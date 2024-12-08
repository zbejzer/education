#include "app.hpp"

#include <chrono>
#include <thread>
#include <cstring>

#include <ncurses/ncurses.h>

#include "game.hpp"

namespace app
{

void initApp(App &_app)
{
    // app variables
    _app.delta_time = 0.0f;
    _app.time_accumulator = 0.0f;
    _app.is_active = true;
    _app.game = nullptr;

    // ncurses configuration
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    // TODO: adjust for resizing terminal windows
    // resizeterm(WINDOW_WIDTH + 2, WINDOW_GAME_HEIGHT + WINDOW_USER_INTERFACE_HEIGHT + 2);
}

void createInterface(App &_app)
{
    // load values from config for easier to read code
    const unsigned int &WINDOW_WIDTH = _app.config->window_width;
    const unsigned int &WINDOW_GAME_HEIGHT = _app.config->window_game_height;
    const unsigned int &WINDOW_USER_INTERFACE_HEIGHT = _app.config->window_ui_height;

    // calculate offsets to center windows
    const unsigned int start_game_row = (LINES - WINDOW_GAME_HEIGHT - WINDOW_USER_INTERFACE_HEIGHT) / 2;
    const unsigned int start_ui_row = start_game_row + WINDOW_GAME_HEIGHT;
    const unsigned int start_col = (COLS - WINDOW_WIDTH) / 2;

    _app.game_window = newwin(WINDOW_GAME_HEIGHT, WINDOW_WIDTH, start_game_row, start_col);
    _app.ui_window = newwin(WINDOW_USER_INTERFACE_HEIGHT, WINDOW_WIDTH, start_ui_row, start_col);
    box(_app.game_window, 0, 0);
    box(_app.ui_window, 0, 0);
}

void deinitApp(App &_app)
{
    clear();
    delwin(_app.game_window);
    delwin(_app.ui_window);
    endwin();
}

// calculate time since last invocation of function in milliseconds
// intended to use to measure time between generated frames
void updateDeltaTime(double &delta_time)
{
    // TODO: Replace STL
    static std::chrono::time_point<std::chrono::steady_clock> last_update;
    static std::chrono::time_point<std::chrono::steady_clock> now;
    now = std::chrono::steady_clock::now();

    delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_update).count() / 1000000.0f;

    last_update = now;
}

void renderApp(App &_app)
{
    entity::printEntity(*_app.game->player, _app.game_window);

    // To improve performance, first copy all
    // windows to logical screen, and then
    // copy the logical screen to physical screen
    wnoutrefresh(_app.game_window);
    wnoutrefresh(_app.ui_window);
    doupdate();
}

void handleInput(App &_app)
{
    int current_read_key;

    for (size_t i = 0; i < 4; i++)
    {
        _app.game->pressed_keys[i] = false;
    }

    while ((current_read_key = getch()) != ERR)
    {
        switch (current_read_key)
        {
        case KEY_F(1):
            _app.is_active = false;
            break;
        case KEY_F(2):
            game::restartGame(*_app.game);
            break;
        case int('w'):
            _app.game->pressed_keys[0] = true; 
            break;
        case int('s'):
            _app.game->pressed_keys[1] = true; 
            break;
        case int('a'):
            _app.game->pressed_keys[2] = true; 
            break;
        case int('d'):
            _app.game->pressed_keys[3] = true; 
            break;
        default:
            break;
        }
    }
}

void drawUserInterface(App &_app)
{
    constexpr char GAME_TITLE[] = "Jumping Frog Game";
    constexpr char CONTROLS[] = "W/A/S/D - poruszanie, F1 - wyjscie z gry, F2 - restart gry";
    char TIME_LEFT_STRING[] = "Pozostaly czas: XXX.XX";
    char KEYBOARD_INPUT_STRING[] = "Nacisniete klawisze: X X X X";
    
    sprintf(TIME_LEFT_STRING, "Pozostaly czas: %6.2f", _app.game->time_left);
    sprintf(KEYBOARD_INPUT_STRING, "Nacisniete klawisze: %d %d %d %d", _app.game->pressed_keys[0], _app.game->pressed_keys[1], _app.game->pressed_keys[2], _app.game->pressed_keys[3]);

    // load values from config for easier to read code
    const unsigned int &WINDOW_WIDTH = _app.config->window_width;
    const unsigned int &WINDOW_USER_INTERFACE_HEIGHT = _app.config->window_ui_height;

    mvwprintw(_app.ui_window, 1, (WINDOW_WIDTH - strlen(GAME_TITLE)) / 2, GAME_TITLE);
    mvwprintw(_app.ui_window, WINDOW_USER_INTERFACE_HEIGHT - 2, (WINDOW_WIDTH - strlen(CONTROLS)) / 2, CONTROLS);
    
    mvwprintw(_app.ui_window, 3, 2, TIME_LEFT_STRING);
    mvwprintw(_app.ui_window, 4, 2, KEYBOARD_INPUT_STRING);
    
    mvwprintw(_app.ui_window, 3, WINDOW_WIDTH - 29, "Autor: Stanislaw Borodziuk");
    mvwprintw(_app.ui_window, 4, WINDOW_WIDTH - 29, "       196034");
    mvwprintw(_app.ui_window, 5, WINDOW_WIDTH - 29, "       Politechnika Gdanska");
}

} // namespace app
#include "display.h"

#include <cstdio>
#include <ncurses/curses.h>

#include "constants.h"

void initScreen(WINDOW **game_window, WINDOW **menu_window)
{
    int start_x, start_y;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_y = (LINES - WINDOW_GAME_HEIGHT) / 2;
    start_x = (COLS - WINDOW_GAME_WIDTH - WINDOW_MENU_WIDTH) / 2;

    *game_window = newwin(WINDOW_GAME_HEIGHT, WINDOW_GAME_WIDTH, start_y, start_x);
    *menu_window = newwin(WINDOW_MENU_HEIGHT, WINDOW_MENU_WIDTH, start_y, start_x + WINDOW_GAME_WIDTH);
    box(*game_window, 0, 0);
    box(*menu_window, 0, 0);
}

void drawBoard(WINDOW **game_window)
{
    constexpr int field_width = 5;
    constexpr int offset_y = 3, offset_x = 2;
    constexpr int offset_num_y = -2, offset_num_x = 0;
    int board_field = 1;
    int x_pos = 0;

    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        printUpperField(game_window, offset_y, x_pos + offset_x, board_field);
        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }

    x_pos = 0;
    int y_start_pos = getmaxy(*game_window) - 1;
    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        printLowerField(game_window, y_start_pos - offset_y, x_pos + offset_x, board_field);
        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }
}

void printUpperField(WINDOW **game_window, const int start_y, const int start_x, const int field_num)
{
    constexpr int offset_num_y = -2, offset_num_x = 0;
    constexpr int field_height = 3;

    char num_string[3];
    sprintf(num_string, "%2d ", field_num);

    wmove(*game_window, start_y + offset_num_y, start_x + offset_num_x);
    wprintw(*game_window, num_string);

    for (size_t y = 0; y < field_height; y++)
    {
        wmove(*game_window, start_y + y, start_x);
        wprintw(*game_window, "===");
    }

    wmove(*game_window, start_y + field_height, start_x);
    wprintw(*game_window, " = ");
}

void printLowerField(WINDOW **game_window, const int start_y, const int start_x, const int field_num)
{
    constexpr int offset_num_y = -2, offset_num_x = 0;
    constexpr int field_height = 3;

    char num_string[3];
    sprintf(num_string, "%2d ", field_num);

    wmove(*game_window, start_y - offset_num_y, start_x + offset_num_x);
    wprintw(*game_window, num_string);

    for (size_t y = 0; y < field_height; y++)
    {
        wmove(*game_window, start_y - y, start_x);
        wprintw(*game_window, "===");
    }

    wmove(*game_window, start_y - field_height, start_x);
    wprintw(*game_window, " = ");
}

/* void drawPlayerPieces(const Player _player)
{
    for (size_t field = 0; field < BOARD_SIZE; field++)
    {
        for (size_t piece = 0; piece < _player.pieces[field]; piece++)
        {
        }
    }
}

void drawBoard()
{
    FILE *board_file = fopen("./assets/img_board.txt", "r");

    if (board_file != NULL)
    {
        for (size_t row = 0; row < WINDOW_GAME_HEIGHT; row++)
        {
            wchar_t line[WINDOW_GAME_WIDTH];
            fread(line, sizeof(wchar_t), WINDOW_GAME_WIDTH, board_file);
            addwstr(line);
        }
    }
}
 */
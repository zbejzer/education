#include "jfrog/app.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "jfrog/game.h"

constexpr unsigned int MAX_STRING_SIZE = 100;

void appInit(App& _app) {
  configInit(_app.config);

  // app variables
  _app.delta_time = 0.0f;
  _app.time_accumulator = 0.0f;
  _app.is_active = true;
  _app.game = nullptr;

  _app.input.skipped_ticks = 0;

  // ncurses configuration
  initscr();
  noecho();
  curs_set(0);
  raw();
  // TODO: adjust for resizing terminal windows
  // resizeterm(WINDOW_WIDTH + 2, WINDOW_GAME_HEIGHT +
  // WINDOW_USER_INTERFACE_HEIGHT + 2);
}

void appCreateInterface(App& _app) {
  // load values from config for easier to read code
  const unsigned int& WINDOW_WIDTH = _app.config.window_width;
  const unsigned int& WINDOW_GAME_HEIGHT = _app.config.window_game_height;
  const unsigned int& WINDOW_USER_INTERFACE_HEIGHT =
      _app.config.window_ui_height;

  // calculate offsets to center windows
  const unsigned int start_game_row =
      (LINES - WINDOW_GAME_HEIGHT - WINDOW_USER_INTERFACE_HEIGHT) / 2;
  const unsigned int start_ui_row = start_game_row + WINDOW_GAME_HEIGHT;
  const unsigned int start_col = (COLS - WINDOW_WIDTH) / 2;

  _app.game_window =
      newwin(WINDOW_GAME_HEIGHT, WINDOW_WIDTH, start_game_row, start_col);
  _app.ui_window = newwin(WINDOW_USER_INTERFACE_HEIGHT, WINDOW_WIDTH,
                          start_ui_row, start_col);

  nodelay(_app.game_window, TRUE);
  keypad(_app.game_window, TRUE);
  notimeout(_app.game_window, TRUE);
  noqiflush();
}

void appDeinit(App& _app) {
  clear();
  delwin(_app.game_window);
  delwin(_app.ui_window);
  endwin();
  configDeinit(_app.config);
}

// calculate time since last invocation of function in milliseconds
// intended to use to measure time between generated frames
void appUpdateDeltaTime(double& delta_time) {
  // TODO: Replace STL
  static std::chrono::time_point<std::chrono::steady_clock> last_update;
  static std::chrono::time_point<std::chrono::steady_clock> now;
  now = std::chrono::steady_clock::now();

  delta_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_update)
          .count() /
      1000000.0f;

  last_update = now;
}

void appRender(App& _app) {
  werase(_app.game_window);
  werase(_app.ui_window);
  entityPrint(*_app.game->player, _app.game_window);

  box(_app.game_window, 0, 0);
  box(_app.ui_window, 0, 0);
  appDrawUserInterface(_app);

  // To improve performance, first copy all
  // windows to logical screen, and then
  // copy the logical screen to physical screen
  wnoutrefresh(_app.game_window);
  wnoutrefresh(_app.ui_window);
  doupdate();
}

void appHandleInput(App& _app) {
  if (_app.input.keys[_app.input.kF1].is_pressed) {
    _app.is_active = false;
  }
  if (_app.input.keys[_app.input.kF2].is_pressed) {
    gameRestart(*_app.game);
  }
}

void appDrawUserInterface(App& _app) {
  // load values from config for easier to read code
  const unsigned int& WINDOW_WIDTH = _app.config.window_width;
  const unsigned int& WINDOW_USER_INTERFACE_HEIGHT =
      _app.config.window_ui_height;

  static const char GAME_TITLE_STRING[MAX_STRING_SIZE] = "Jumping Frog Game";
  static const char CONTROLS_STRING[MAX_STRING_SIZE] =
      "W/A/S/D - poruszanie, F1 - wyjscie z gry, F2 - restart gry";
  static char TIME_LEFT_STRING[MAX_STRING_SIZE];
  static char FPS_STRING[MAX_STRING_SIZE];

  sprintf(TIME_LEFT_STRING, "Pozostaly czas: %6.2f", _app.game->time_left);
  sprintf(FPS_STRING, "FPS: %8d", int(1000.0f / _app.delta_time));

  mvwprintw(_app.ui_window, 1, (WINDOW_WIDTH - strlen(GAME_TITLE_STRING)) / 2,
            GAME_TITLE_STRING);
  mvwprintw(_app.ui_window, WINDOW_USER_INTERFACE_HEIGHT - 2,
            (WINDOW_WIDTH - strlen(CONTROLS_STRING)) / 2, CONTROLS_STRING);

  mvwprintw(_app.ui_window, 3, 2, TIME_LEFT_STRING);
  mvwprintw(_app.ui_window, 4, 2, FPS_STRING);

  mvwprintw(_app.ui_window, 3, WINDOW_WIDTH - 29, "Autor: Stanislaw Borodziuk");
  mvwprintw(_app.ui_window, 4, WINDOW_WIDTH - 29, "       196034");
  mvwprintw(_app.ui_window, 5, WINDOW_WIDTH - 29,
            "       Politechnika Gdanska");
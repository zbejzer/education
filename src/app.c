#include "jfrog/app.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "jfrog/game.h"

const unsigned int MAX_STRING_SIZE = 100;

void appInit(App *_app)
{
    renderInit(&_app->screen);
    inputInit(&_app->input);

    _app->delta_time = 0.0f;
    _app->time_accumulator = 0.0f;
    _app->is_active = true;
}

void appDeinit(App *_app)
{
    // clear();
    // delwin(_app->game_window);
    // delwin(_app->ui_window);
    // endwin();
    // configDeinit(_app->config);
}

// calculate time since last invocation of function in milliseconds
// intended to use to measure time between generated frames
void appUpdateDeltaTime(double *delta_time)
{
    // // TODO: Replace STL
    // static std::chrono::time_point<std::chrono::steady_clock> last_update;
    // static std::chrono::time_point<std::chrono::steady_clock> now;
    // now = std::chrono::steady_clock::now();

    // delta_time =
    //     std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_update)
    //         .count() /
    //     1000000.0f;

    // last_update = now;
}

void appHandleInput(App *_app)
{
    // if (_app->input.keys[_app->input.kF1].is_pressed) {
    //   _app->is_active = false;
    // }
    // if (_app->input.keys[_app->input.kF2].is_pressed) {
    //   gameRestart(*_app->game);
    // }
}

App *k_app = NULL;
const unsigned int TICKRATE = 64;
const double TICK_DURATION = 1000.0f / TICKRATE;
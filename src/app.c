#include "jfrog/app.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "jfrog/game.h"

const unsigned int MAX_STRING_SIZE = 100;

void appInit(App *_app)
{
    _app->t_accumulator = 0.0;
    _app->is_active = true;

    renderInit(&_app->screen);
    inputInit(&_app->input);

    return;
}

void appDeinit(App *_app)
{
    renderDeinit(&_app->screen);
    inputDeinit(&_app->input);

    return;
}

// calculate time since last invocation of function
// intended to use to measure time between generated frames
void appUpdateDeltaTime(App *_app)
{
    timespec_get(&_app->t_now, TIME_UTC);
    double s = (double)(_app->t_now.tv_sec - _app->t_last_update.tv_sec);
    double ns = (double)(_app->t_now.tv_nsec - _app->t_last_update.tv_nsec);

    _app->t_delta = s * 1000.0 + (ns / 1000000.0);

    _app->t_last_update = _app->t_now;
}

void appHandleInput(App *_app)
{
    if (_app->input.keys[JFROG_KEY_QUIT])
    {
        _app->is_active = false;
    }
}

App *k_app = NULL;
const unsigned int TICKRATE = 64;
const double TICK_DURATION = 1000.0 / TICKRATE;
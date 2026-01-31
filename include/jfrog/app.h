#ifndef JFROG_APP_H
#define JFROG_APP_H

#include <stdbool.h>
#include <time.h>

#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"
#include "jfrog/render.h"

typedef struct App
{
    struct timespec t_last_update, t_now;
    double t_delta;       // measured in milliseconds
    double t_accumulator; // measured in milliseconds
    bool is_active;
    Input input;
    Screen screen;
} App;

void appInit(App *_app);
void appDeinit(App *_app);
void appUpdateDeltaTime(App *_app);
void appHandleInput(App *_app);

extern App *k_app;
// frequency of ticks per second
extern const unsigned int TICKRATE;
// single tick duration in milliseconds
extern const double TICK_DURATION;

#endif
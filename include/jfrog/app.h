#ifndef JFROG_APP_H
#define JFROG_APP_H

#include <stdbool.h>

#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"
#include "jfrog/render.h"

typedef struct App {
  double delta_time;  // measured in milliseconds
  double time_accumulator;
  bool is_active;
  Input input;
  Screen screen;
} App;

void appInit(App* _app);
void appCreateInterface(App* _app);
void appDeinit(App* _app);
void appUpdateDeltaTime(double* delta_time);
void appRender(App* _app);
void appHandleInput(App* _app);
void appDrawUserInterface(App* _app);

extern App* k_app;
// frequency of ticks per second
extern const unsigned int TICKRATE;
// single tick duration in milliseconds
extern const double TICK_DURATION;

#endif
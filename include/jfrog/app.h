#ifndef JFROG_APP_H
#define JFROG_APP_H

#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"

constexpr unsigned int TICKRATE = 64;  // frequency of ticks per second
constexpr double TICK_DURATION =
    1000.0f / TICKRATE;  // single tick duration in milliseconds

struct App {
  double delta_time;  // measured in milliseconds
  double time_accumulator;
  bool is_active;
  Game* game;
  Config config;
  Input input;

  WINDOW *game_window, *ui_window;
};

void appInit(App& _app);
void appCreateInterface(App& _app);
void appDeinit(App& _app);
void appUpdateDeltaTime(double& delta_time);
void appRender(App& _app);
void appHandleInput(App& _app);
void appDrawUserInterface(App& _app);

#endif
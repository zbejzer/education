#ifndef APP_H
#define APP_H

#include <ncurses/ncurses.h>

#include "config.hpp"
#include "game.hpp"
#include "input.hpp"

namespace app
{

constexpr unsigned int TICKRATE = 64;                // frequency of ticks per second
constexpr double TICK_DURATION = 1000.0f / TICKRATE; // single tick duration in milliseconds

struct App
{
    double delta_time; // measured in milliseconds
    double time_accumulator;
    bool is_active;
    game::Game *game;
    config::Config config;
    input::Input input;

    WINDOW *game_window, *ui_window;
};

void initApp(App &_app);
void createInterface(App &_app);
void deinitApp(App &_app);
void updateDeltaTime(double &delta_time);
void renderApp(App &_app);
void handleInput(App &_app);
void drawUserInterface(App &_app);

} // namespace app

#endif
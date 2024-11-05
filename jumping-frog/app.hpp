#ifndef APP_H
#define APP_H

namespace app
{

constexpr int TICKRATE = 64;                         // frequency of ticks per second
constexpr double TICK_DURATION = 1000.0f / TICKRATE; // single tick duration in milliseconds

struct App
{
    double delta_time; // measured in milliseconds
    double time_accumulator;
    bool is_active;
};

void initApp(App &_app);
void updateDeltaTime(double &delta_time);
void renderApp();
void handleInput();
void doAction();

} // namespace app

#endif
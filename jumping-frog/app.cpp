#include "app.hpp"

#include <chrono>
#include <thread>

#include <ncurses/ncurses.h>

namespace app
{

void initApp(App &_app)
{
    _app.delta_time = 0.0f;
    _app.time_accumulator = 0.0f;
    _app.is_active = true;
}

// calculate time since last invocation of function in milliseconds
// intended to use to measure time between generated frames
void updateDeltaTime(double &delta_time)
{
    static std::chrono::time_point<std::chrono::steady_clock> last_update;
    static std::chrono::time_point<std::chrono::steady_clock> now;
    now = std::chrono::steady_clock::now();

    delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_update).count() / 1000000.0f;

    last_update = now;
}

void renderApp()
{
    refresh();
}

void handleInput()
{
}

void doAction()
{
}

void drawUserInterface()
{
}

} // namespace app
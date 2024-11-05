#include "app.hpp"

#include <string>

#include <ncurses/ncurses.h>

int main()
{
    app::App app;
    app::initApp(app);
    app::updateDeltaTime(app.delta_time); // set starting values for static variables

    initscr();
    cbreak();
    noecho();

    mvaddch(0, 0, '+');
    mvaddch(LINES - 1, 0, '-');

    // main game loop
    while (app.is_active)
    {
        app::updateDeltaTime(app.delta_time);
        app.time_accumulator += app.delta_time;

        while (app.time_accumulator > app::TICK_DURATION)
        {
            app::doAction();
        }

        mvaddstr(10, 30, std::to_string(1.0 / app.delta_time).c_str());
        app::renderApp();
    }

    getch();

    endwin();
}
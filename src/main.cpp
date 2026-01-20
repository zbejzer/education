#include <ncurses/ncurses.h>

#include "app.hpp"
#include "config.hpp"
#include "game.hpp"
#include "input.hpp"

int main()
{
    app::App app;
    app::initApp(app);
    app::createInterface(app);
    app::updateDeltaTime(app.delta_time); // set starting values for static variables

    game::Game game;
    game.config = &app.config;
    game::initGame(game);
    app.game = &game;

    input::setInputDownState(app.input, false);
    input::setInputPressedState(app.input, false);
    input::setInputReleasedState(app.input, false);

    // main game loop
    while (app.is_active)
    {
        app::updateDeltaTime(app.delta_time);
        app.time_accumulator += app.delta_time;

        while (app.time_accumulator > app::TICK_DURATION)
        {
            input::pollInput(app.input, app.game_window);
            app::handleInput(app);

            if (!game.is_paused)
            {
                game.time_left -= app::TICK_DURATION / 1000.0f;
                game::doPlayerMovement(game, app.input);
            }

            // clear one-time flags
            input::setInputPressedState(app.input, false);
            input::setInputReleasedState(app.input, false);

            app.time_accumulator -= app::TICK_DURATION;
        }

        app::renderApp(app);
    }

    game::deinitGame(game);
    app::deinitApp(app);
}
#include <ncurses/ncurses.h>

#include "app.hpp"
#include "game.hpp"
#include "config.hpp"

int main()
{
    config::Config config;
    config::initConfig(config);

    app::App app;
    app.config = &config;
    app::initApp(app);
    app::createInterface(app);
    app::updateDeltaTime(app.delta_time); // set starting values for static variables
    
    game::Game game;
    game.config = &config;
    game::initGame(game);
    app.game = &game;

    // main game loop
    while (app.is_active)
    {
        app::updateDeltaTime(app.delta_time);
        app.time_accumulator += app.delta_time;

        app::handleInput(app);
        
        while (app.time_accumulator > app::TICK_DURATION)
        {
            if(!game.is_paused)
            {
                game.time_left -= app::TICK_DURATION / 1000.0f;
                game::doPlayerMovement(game);
            }
            app.time_accumulator -= app::TICK_DURATION;
        }

        app::drawUserInterface(app);
        app::renderApp(app);
    }

    game::deinitGame(game);
    app::deinitApp(app);
    config::deinitConfig(config);
}
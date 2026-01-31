#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"
#include "jfrog/render.h"

int main()
{
    Config config;
    configInit(&config);
    k_config = &config;

    App app;
    appInit(&app);
    k_app = &app;
    // appCreateInterface(&app);
    // set starting values for static variables
    // appUpdateDeltaTime(&app.delta_time);

    Game game;
    gameInit(&game);
    k_game = &game;

    renderHideCursor();
    renderClearConsole();
    renderClearBuffer(&app.screen);

    // inputSetDownState(&app.input, false);
    // inputSetPressedState(&app.input, false);
    // inputSetReleasedState(&app.input, false);

    // main game loop
    while (k_app->is_active)
    {
        // appUpdateDeltaTime(&app.delta_time);
        // app.time_accumulator += app.delta_time;

        // while (app.time_accumulator > TICK_DURATION) {
        //   // inputPoll(&app.input, app.game_window);
        //   // appHandleInput(&app);

        //   // if (!game.is_paused) {
        //   //   game.time_left -= TICK_DURATION / 1000.0f;
        //   //   gameDoPlayerMovement(&game, app.input);
        //   // }

        //   // // clear one-time flags
        //   // inputSetPressedState(&app.input, false);
        //   // inputSetReleasedState(&app.input, false);

        //   // app.time_accumulator -= TICK_DURATION;
        // }
        renderClearBuffer(&app.screen);
        renderCreateUi(&app.screen);
        renderDrawBuffer(&app.screen);
    }

    renderShowCursor();

    gameDeinit(&game);
    appDeinit(&app);
    configDeinit(&config);
}
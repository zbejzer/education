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

    Game game;
    gameInit(&game);
    k_game = &game;

    renderHideCursor();
    renderClearConsole();
    renderClearBuffer(&app.screen);

    // acts as initialization of internal time var
    appUpdateDeltaTime(&app);

    // main game loop
    while (app.is_active)
    {
        appUpdateDeltaTime(&app);
        app.t_accumulator += app.t_delta;
        game.time_left -= app.t_delta;

        // while (app.t_accumulator > TICK_DURATION) {
        //   // inputPoll(&app.input, app.game_window);
        //   // appHandleInput(&app);

        //   // if (!game.is_paused) {
        //   //   game.time_left -= TICK_DURATION / 1000.0f;
        //   //   gameDoPlayerMovement(&game, app.input);
        //   // }

        //   // // clear one-time flags
        //   // inputSetPressedState(&app.input, false);
        //   // inputSetReleasedState(&app.input, false);

        //   // app.t_accumulator -= TICK_DURATION;
        // }

        inputPoll(&app.input);
        appHandleInput(&app);

        renderClearBuffer(&app.screen);
        renderCreateUi(&app.screen);
        renderDrawBuffer(&app.screen);

        if (game.time_left <= 0.0f)
        {
            app.is_active = false;
        }
    }

    renderShowCursor();

    gameDeinit(&game);
    appDeinit(&app);
    configDeinit(&config);
}
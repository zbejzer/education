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

        while (app.t_accumulator > TICK_DURATION)
        {
            inputPoll(&app.input);
            appHandleInput(&app);

            game.time_left -= TICK_DURATION / 1000.0f;
            gameDoPlayerMovement(&game, &app.input);

            app.t_accumulator -= TICK_DURATION;

            // if (game.time_left <= 0.0)
            // {
            //     app.is_active = false;
            // }
        }

        renderClearBuffer(&app.screen);
        renderCreateUi(&app.screen);

        gameRenderEntities(&game, &app.screen);

        renderDrawBuffer(&app.screen);
    }

    renderShowCursor();

    gameDeinit(&game);
    appDeinit(&app);
    configDeinit(&config);
}
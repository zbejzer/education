#include <stdlib.h>
#include <time.h>

#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"
#include "jfrog/render.h"

int main()
{
    srand(time(NULL));

    unsigned int score_tick_accumulator = 0;
    unsigned int game_speedup_tick_accumulator = 0;

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

            game.time_passed += TICK_DURATION / 1000.0f;
            score_tick_accumulator++;
            game_speedup_tick_accumulator++;

            if (score_tick_accumulator >= TICKRATE)
            {
                game.score += 10;
                score_tick_accumulator -= TICKRATE;
            }
            if (game_speedup_tick_accumulator >= 5 * TICKRATE)
            {
                game.board_scroll_speed += 0.2;
                game_speedup_tick_accumulator -= 5 * TICKRATE;
            }

            gameDoPlayerMovement(&game, &app.input);
            gameDoCarRowsMovement(&game);

            if (gameCheckPlayerCollision(&game))
            {
                app.is_active = false;
            }

            app.t_accumulator -= TICK_DURATION;
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
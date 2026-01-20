#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/game.h"
#include "jfrog/input.h"

int main() {
  Config config;
  configInit(&config);

  App app;
  appInit(&app);
  appCreateInterface(&app);
  // set starting values for static variables
  appUpdateDeltaTime(&app.delta_time);

  Game game;
  game.config = &app.config;
  gameInit(&game);
  app.game = &game;

  inputSetDownState(&app.input, false);
  inputSetPressedState(&app.input, false);
  inputSetReleasedState(&app.input, false);

  // main game loop
  while (app.is_active) {
    appUpdateDeltaTime(&app.delta_time);
    app.time_accumulator += app.delta_time;

    while (app.time_accumulator > TICK_DURATION) {
      inputPoll(&app.input, app.game_window);
      appHandleInput(&app);

      if (!game.is_paused) {
        game.time_left -= TICK_DURATION / 1000.0f;
        gameDoPlayerMovement(&game, app.input);
      }

      // clear one-time flags
      inputSetPressedState(&app.input, false);
      inputSetReleasedState(&app.input, false);

      app.time_accumulator -= TICK_DURATION;
    }

    appRender(&app);
  }

  gameDeinit(&game);
  appDeinit(&app);
}
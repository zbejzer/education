#ifndef JFROG_GAME_H
#define JFROG_GAME_H

#include <stdbool.h>

#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

typedef struct Game {
  bool is_paused;
  float time_left;

  Entity* player;
  Entity* cars;

  Config* config;
} Game;

void gameInit(Game* _game);
void gameDeinit(Game* _game);
void gameRestart(Game* _game);
void gameDoPlayerMovement(Game* _game, Input* input);

#endif
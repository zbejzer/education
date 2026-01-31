#ifndef JFROG_GAME_H
#define JFROG_GAME_H

#include <stdbool.h>

#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

typedef struct Game
{
    float time_left;
    unsigned int board_offset;
    unsigned int score;

    Entity *player;
    Entity *cars;
} Game;

void gameInit(Game *_game);
void gameDeinit(Game *_game);
void gameDoPlayerMovement(Game *_game, Input *input);

extern Game *k_game;

#endif
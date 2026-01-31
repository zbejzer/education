#ifndef JFROG_GAME_H
#define JFROG_GAME_H

#include <stdbool.h>

#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

typedef struct Game
{
    double time_passed;
    unsigned int board_offset;
    unsigned int score;
    float board_scroll_speed;

    Entity *player;
    CarRow car_rows[5];
} Game;

void gameInit(Game *_game);
void gameDeinit(Game *_game);
void gameDoPlayerMovement(Game *_game, Input *input);
void gameDoSingleCarRowMovement(Game *_game, CarRow *_row);
void gameDoCarRowsMovement(Game *_game);
void gameRenderEntities(Game *_game, Screen *const _screen);
int gameCheckPlayerCollision(Game *_game);

extern Game *k_game;

#endif
#include "jfrog/game.h"

#include <stdlib.h>

#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

void gameInit(Game *_game)
{
    _game->is_paused = true;

    _game->time_left = k_config->time_limit;
    _game->player = (Entity *)malloc(sizeof(Entity));
    _game->cars = (Entity *)malloc(sizeof(Entity) * k_config->cars_count);

    // entityInitPlayer(_game->player);
}

void gameDeinit(Game *_game)
{
    // entityDeinit(_game->player);

    // for (size_t i = 0; i < _game->config->cars_count; i++)
    // {
    //     entityDeinit(_game->cars[i]);
    // }

    free(_game->player);
    free(_game->cars);
}

void gameRestart(Game *_game)
{
    // _game->is_paused = false;
    // _game->time_left = _game->config->time_limit;
}

void gameDoPlayerMovement(Game *_game, Input *input)
{
    // const Config config = *_game->config;

    // Entity* player = _game->player;

    // if (input.keys[input.kUp].is_down) {
    //   player->pos_y -= player->speed * TICK_DURATION / 1000.0f;
    // }
    // if (input.keys[input.kDown].is_down) {
    //   player->pos_y += player->speed * TICK_DURATION / 1000.0f;
    // }
    // if (input.keys[input.kLeft].is_down) {
    //   player->pos_x -= player->speed * TICK_DURATION / 1000.0f;
    // }
    // if (input.keys[input.kRight].is_down) {
    //   player->pos_x += player->speed * TICK_DURATION / 1000.0f;
    // }

    // // check for out of bounds position
    // if (player->pos_x + float(player->width) > float(config.game_max_x)) {
    //   player->pos_x = float(config.game_max_x - player->width);
    // } else if (player->pos_x < float(config.game_min_x)) {
    //   player->pos_x = float(config.game_min_x);
    // }
    // if (player->pos_y + float(player->height) > float(config.game_max_y)) {
    //   player->pos_y = float(config.game_max_y - player->height);
    // } else if (player->pos_y < float(config.game_min_y)) {
    //   player->pos_y = float(config.game_min_y);
    // }
}

Game *k_game = NULL;
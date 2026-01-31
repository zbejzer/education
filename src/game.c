#include "jfrog/game.h"

#include <stdlib.h>

#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

void gameInit(Game *_game)
{
    _game->time_left = (double)k_config->time_limit;
    _game->board_offset = 0;
    _game->score = 0;

    _game->player = (Entity *)malloc(sizeof(Entity));
    _game->cars = (Entity *)malloc(sizeof(Entity) * k_config->cars_count);

    entityInitPlayer(_game->player);
}

void gameDeinit(Game *_game)
{
    entityDeinit(_game->player);

    // for (size_t i = 0; i < _game->config->cars_count; i++)
    // {
    //     entityDeinit(_game->cars[i]);
    // }

    free(_game->player);
    free(_game->cars);
}

void gameDoPlayerMovement(Game *_game, Input *_input)
{
    Entity *player = _game->player;

    if (_input->keys[JFROG_KEY_LEFT])
    {
        player->pos_x -= player->speed * TICK_DURATION / 1000.0f;
    }
    if (_input->keys[JFROG_KEY_RIGHT])
    {
        player->pos_x += player->speed * TICK_DURATION / 1000.0f;
    }

    // check for out of bounds position
    if (player->pos_x + (float)player->width > (float)k_config->area_width)
    {
        player->pos_x = (float)k_config->area_width - (float)player->width;
    }
    else if (player->pos_x < 0)
    {
        player->pos_x = 0;
    }
}

void gameRenderEntities(Game *_game, Screen *const _screen)
{
    entityPrint(_game->player, _screen);
}

Game *k_game = NULL;
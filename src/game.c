#include "jfrog/game.h"

#include <stdlib.h>

#include "jfrog/app.h"
#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

void gameInit(Game *_game)
{
    _game->time_passed = (double)k_config->time_limit;
    _game->board_offset = 0;
    _game->score = 0;
    _game->board_scroll_speed = 3.0;

    _game->player = (Entity *)malloc(sizeof(Entity));

    entityInitPlayer(_game->player);

    for (size_t i = 0; i < sizeof(_game->car_rows) / sizeof(_game->car_rows[0]); i++)
    {
        entityInitCarRow(&_game->car_rows[i]);
    }
}

void gameDeinit(Game *_game)
{
    entityDeinit(_game->player);

    for (size_t i = 0; i < sizeof(_game->car_rows) / sizeof(_game->car_rows[0]); i++)
    {
        entityDeinitCarRow(&_game->car_rows[i]);
    }

    free(_game->player);
}

void gameDoPlayerMovement(Game *_game, Input *_input)
{
    Entity *player = _game->player;

    if (_input->keys[JFROG_KEY_LEFT])
    {
        player->pos_x -= k_config->player_speed * TICK_DURATION / 1000.0f;
    }
    if (_input->keys[JFROG_KEY_RIGHT])
    {
        player->pos_x += k_config->player_speed * TICK_DURATION / 1000.0f;
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

void gameDoSingleCarRowMovement(Game *_game, CarRow *_row)
{
    const size_t cars_count = sizeof(_row->cars) / sizeof(_row->cars[0]);
    Entity *first_car = NULL;

    for (size_t i = 0; i < cars_count; i++)
    {
        if (_row->cars[i].active)
        {
            _row->cars[i].pos_x += k_config->car_speed * TICK_DURATION / 1000.0f;

            if (first_car == NULL || _row->cars[i].pos_x < first_car->pos_x)
            {
                first_car = &_row->cars[i];
            }
        }

        if ((int)_row->cars[i].pos_x > (int)k_config->area_width)
        {
            _row->cars[i].pos_x = (float)(-1 * k_config->car_width);
            _row->cars[i].active = false;
        }

        _row->cars[i].pos_y = _row->pos_y;
    }

    if (first_car == NULL || first_car->pos_x > k_config->car_inrow_break)
    {
        for (size_t i = 0; i < cars_count; i++)
        {
            if (!_row->cars[i].active)
            {
                _row->cars[i].pos_x = (float)((-1) * (int)k_config->car_width);
                _row->cars[i].active = true;
                break;
            }
        }
    }
}

void gameDoCarRowsMovement(Game *_game)
{
    const size_t car_rows_count = sizeof(_game->car_rows) / sizeof(_game->car_rows[0]);
    CarRow *highest_active_row = NULL;

    for (size_t i = 0; i < car_rows_count; i++)
    {
        if (_game->car_rows[i].active)
        {
            _game->car_rows[i].pos_y += _game->board_scroll_speed * TICK_DURATION / 1000.0f;

            gameDoSingleCarRowMovement(_game, &_game->car_rows[i]);

            if (highest_active_row == NULL || _game->car_rows[i].pos_y < highest_active_row->pos_y)
            {
                highest_active_row = &_game->car_rows[i];
            }
        }

        if ((int)_game->car_rows[i].pos_y > (int)k_config->area_game_height)
        {
            _game->car_rows[i].pos_y = (float)(-1 * k_config->car_height);
            _game->car_rows[i].active = false;
        }
    }

    if (highest_active_row == NULL || highest_active_row->pos_y > k_config->car_row_break)
    {
        for (size_t i = 0; i < car_rows_count; i++)
        {
            if (!_game->car_rows[i].active)
            {
                _game->car_rows[i].pos_y = (float)((-1) * (int)k_config->car_height);
                _game->car_rows[i].active = true;
                break;
            }
        }
    }
}

void gameRenderEntities(Game *_game, Screen *const _screen)
{
    entityPrint(_game->player, _screen);

    for (size_t i = 0; i < sizeof(_game->car_rows) / sizeof(_game->car_rows[0]); i++)
    {
        if (_game->car_rows[i].active)
        {
            for (size_t j = 0; j < sizeof(_game->car_rows[i].cars) / sizeof(_game->car_rows[i].cars[0]); j++)
            {
                if (_game->car_rows[i].cars[j].active)
                {
                    entityPrint(&_game->car_rows[i].cars[j], _screen);
                }
            }
        }
    }
}

int gameCheckPlayerCollision(Game *_game)
{
    for (size_t row = 0; row < sizeof(_game->car_rows) / sizeof(_game->car_rows[0]); row++)
    {
        if (_game->car_rows[row].active)
        {
            for (size_t i = 0; i < sizeof(_game->car_rows[row].cars) / sizeof(_game->car_rows[row].cars[0]); i++)
            {
                if (_game->car_rows[row].cars[i].active &&
                    entityCheckCollision(_game->player, &_game->car_rows[row].cars[i]))
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

Game *k_game = NULL;

#include "jfrog/entity.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "jfrog/config.h"
#include "jfrog/render.h"

void entityInitPlayer(Entity *_player)
{
    _player->active = true;
    _player->width = k_config->player_width;
    _player->height = k_config->player_height;
    _player->pos_y = (float)(k_config->area_game_height - k_config->player_height - 1);
    _player->pos_x = (k_config->window_width - k_config->player_width) / 2.0f + 1;
    _player->sprite = (char *)malloc(sizeof(char) * (_player->width * _player->height + 1));

    for (unsigned int i = 0; i < _player->height; i++)
    {
        for (unsigned int j = 0; j < _player->width; j++)
        {
            _player->sprite[i * _player->width + j] = k_config->player_sprite[i * _player->width + j];
        }
    }
}

void entityInitCar(Entity *_car)
{
    _car->active = true;
    _car->width = k_config->car_width;
    _car->height = k_config->car_height;
    _car->pos_y = k_config->car_height + 1; // off-screen
    _car->pos_x = 0;
    _car->sprite = (char *)malloc(sizeof(char) * (_car->width * _car->height + 1));

    for (unsigned int i = 0; i < _car->height; i++)
    {
        for (unsigned int j = 0; j < _car->width; j++)
        {
            _car->sprite[i * _car->width + j] = k_config->car_sprite[i * _car->width + j];
        }
    }
}

void entityDeinit(Entity *_entity)
{
    free(_entity->sprite);
}

void entityPrint(Entity *_entity, Screen *const _screen)
{
    for (unsigned int y = 0; y < _entity->height; y++)
    {
        for (unsigned int x = 0; x < _entity->width; x++)
        {
            int final_x = (int)(_entity->pos_x + (float)x);
            int final_y = (int)(_entity->pos_y + (float)y);

            if (final_x >= 0 &&                        //
                final_x < (int)k_config->area_width && //
                final_y >= 0 &&                        //
                final_y < (int)k_config->area_game_height)
            {
                renderPutCharGame(_screen, _entity->sprite[y * _entity->width + x], final_x, final_y);
            }
        }
    }
}

int entityCheckCollision(Entity *a, Entity *b)
{
    int a_left = (int)a->pos_x;
    int a_right = (int)a->pos_x + (int)a->width;
    int a_top = (int)a->pos_y;
    int a_bottom = (int)a->pos_y + (int)a->height;

    int b_left = (int)b->pos_x;
    int b_right = (int)b->pos_x + (int)b->width;
    int b_top = (int)b->pos_y;
    int b_bottom = (int)b->pos_y + (int)b->height;

    if (a_right <= b_left || a_left >= b_right)
    {
        return 0;
    }
    if (a_bottom <= b_top || a_top >= b_bottom)
    {
        return 0;
    }

    return 1;
}

void entityInitCarRow(CarRow *_row)
{
    _row->pos_y = 0.0;
    _row->active = false;
    _row->concurent_cars = 2;

    unsigned int row_offset = rand() % k_config->car_inrow_break;

    for (unsigned int i = 0; i < sizeof(_row->cars) / sizeof(_row->cars[0]); i++)
    {
        entityInitCar(&_row->cars[i]);
        _row->cars[i].pos_x += (k_config->car_inrow_break + k_config->car_width) * i + row_offset;
    }
}

void entityDeinitCarRow(CarRow *_row)
{
    for (unsigned int i = 0; i < sizeof(_row->cars) / sizeof(_row->cars[0]); i++)
    {
        entityDeinit(&_row->cars[i]);
    }
}
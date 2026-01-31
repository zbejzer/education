
#include "jfrog/entity.h"

#include <stdlib.h>
#include <string.h>

#include "jfrog/config.h"
#include "jfrog/render.h"

void entityInitPlayer(Entity *_player)
{
    _player->width = k_config->player_width;
    _player->height = k_config->player_height;
    _player->pos_y = (float)(k_config->area_game_height - k_config->player_height - 1);
    _player->pos_x = (k_config->window_width - k_config->player_width) / 2.0f + 1;
    _player->speed = k_config->player_speed;
    _player->sprite = (char *)malloc(sizeof(char) * (_player->width * _player->height + 1));

    for (unsigned int i = 0; i < _player->height; i++)
    {
        for (unsigned int j = 0; j < _player->width; j++)
        {
            _player->sprite[i * _player->width + j] = k_config->player_sprite[i * _player->width + j];
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
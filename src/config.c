#include "jfrog/config.h"

#include <stdlib.h>
#include <string.h>

void configInit(Config *_config)
{
    _config->fps_limit = 256;

    _config->window_width = 80;
    _config->window_game_height = 16;
    _config->window_ui_height = 6;

    _config->border_size = 1;

    _config->area_width = _config->window_width - 2 * _config->border_size;
    _config->area_game_height = _config->window_game_height - 2 * _config->border_size;
    _config->area_ui_height = _config->window_ui_height - 2 * _config->border_size;

    _config->player_height = 3;
    _config->player_width = 3;
    _config->car_height = 2;
    _config->car_width = 3;
    _config->time_limit = 30;

    _config->player_sprite = (char *)malloc(sizeof(char) * (_config->player_height * _config->player_width + 1));
    _config->car_sprite = (char *)malloc(sizeof(char) * (_config->car_height * _config->car_width + 1));

    strcpy(_config->player_sprite, "* *"
                                   "***"
                                   "***");

    strcpy(_config->car_sprite, "###"
                                "###");

    _config->player_speed = 10.0f;

    _config->cars_count = 5;
}

void configDeinit(Config *_config)
{
    free(_config->player_sprite);
    free(_config->car_sprite);
}

Config *k_config = NULL;
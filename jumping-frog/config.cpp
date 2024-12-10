#include "config.hpp"

#include <cstring>

namespace config
{

void initConfig(Config &_config)
{
    _config.fps_limit = 256;

    _config.window_width = 80;
    _config.window_game_height = 22;
    _config.window_ui_height = 8;

    _config.game_min_y = 1;
    _config.game_max_y = _config.window_game_height - 1;
    _config.game_min_x = 1;
    _config.game_max_x = _config.window_width - 1;

    _config.player_height = 3;
    _config.player_width = 3;
    _config.car_height = 2;
    _config.car_width = 3;
    _config.time_limit = 60;

    _config.player_sprite = new char[_config.player_height * _config.player_width + 1];
    _config.car_sprite = new char[_config.player_height * _config.player_width + 1];

    strcpy(_config.player_sprite, "* *"
                                  "***"
                                  "***");

    strcpy(_config.car_sprite, "###"
                               "###");

    _config.player_speed = 1.0f;

    _config.cars_count = 5;
}

void deinitConfig(Config &_config)
{
    delete _config.player_sprite;
    delete _config.car_sprite;
}
} // namespace config
#ifndef JFROG_CONFIG_H
#define JFROG_CONFIG_H

typedef struct Config
{
    unsigned int fps_limit;

    unsigned int window_width, window_game_height, window_ui_height;
    unsigned int border_size;
    unsigned int area_width, area_game_height, area_ui_height;

    unsigned int player_width, player_height;
    char *player_sprite;
    float player_speed;

    unsigned int car_width, car_height;
    char *car_sprite;
    float car_speed;

    unsigned int time_limit;
    unsigned int car_row_break;
    unsigned int car_inrow_break;
} Config;

void configInit(Config *_config);
void configDeinit(Config *_config);

extern Config *k_config;

#endif
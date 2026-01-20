#ifndef JFROG_CONFIG_H
#define JFROG_CONFIG_H

typedef struct Config {
  unsigned int fps_limit;

  unsigned int window_width, window_game_height, window_ui_height;
  unsigned int border_size;
  unsigned int area_width, area_game_height, area_ui_height;

  unsigned int player_width, player_height;
  int player_color;
  char* player_sprite;
  float player_speed;

  unsigned int car_width, car_height;
  int car_color;
  char* car_sprite;
  float car_speed_1;
  float car_speed_2;

  unsigned int time_limit;
  unsigned int cars_count;
} Config;

void configInit(Config* _config);
void configDeinit(Config* _config);

extern Config* k_config;

#endif
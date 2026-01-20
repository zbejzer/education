
#include "jfrog/entity.h"

#include <stdlib.h>

#include "jfrog/config.h"

// void entityInitPlayer(Entity* _player) {
//   _player->width = k_config->player_width;
//   _player->height = k_config->player_height;
//   _player->pos_y =
//       float(k_config->window_game_height - k_config->player_height - 1);
//   _player->pos_x = (k_config->window_width - k_config->player_width) / 2.0f +
//   1; _player->speed = k_config->player_speed; _player->color =
//   k_config->player_color; _player->sprite =
//       (char*)malloc(sizeof(char) * (_player->width * _player->height + 1));

//   for (int i = 0; i < _player->height; i++) {
//     for (int j = 0; j < _player->width; j++) {
//       _player->sprite[i * _player->width + j] =
//           k_config->player_sprite[i * _player->width + j];
//     }
//   }
// }

// void entityDeinit(Entity* _entity) { free(_entity->sprite); }

// void entityPrint(Entity* _entity, WINDOW* _window) {
//   for (int y = 0; y < _entity->height; y++) {
//     for (int x = 0; x < _entity->width; x++) {
//       mvwaddch(_window, y + _entity->pos_y, x + _entity->pos_x,
//                _entity->sprite[y * _entity->width + x]);
//     }
//   }
// }
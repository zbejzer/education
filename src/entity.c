#include "jfrog/entity.h"

#include "jfrog/config.h"

void entityInitPlayer(Entity& _player, Config& _config) {
  _player.width = _config.player_width;
  _player.height = _config.player_height;
  _player.pos_y = float(_config.window_game_height - _config.player_height - 1);
  _player.pos_x = (_config.window_width - _config.player_width) / 2.0f + 1;
  _player.speed = _config.player_speed;
  _player.color = _config.player_color;
  _player.sprite = new char[_player.width * _player.height + 1];

  for (int i = 0; i < _player.height; i++) {
    for (int j = 0; j < _player.width; j++) {
      _player.sprite[i * _player.width + j] =
          _config.player_sprite[i * _player.width + j];
    }
  }
}

void entityDeinit(Entity& _entity) { delete _entity.sprite; }

void entityPrint(Entity& _entity, WINDOW* _window) {
  for (int y = 0; y < _entity.height; y++) {
    for (int x = 0; x < _entity.width; x++) {
      mvwaddch(_window, y + _entity.pos_y, x + _entity.pos_x,
               _entity.sprite[y * _entity.width + x]);
    }
  }
}
#ifndef JFROG_GAME_H
#define JFROG_GAME_H

#include "jfrog/config.h"
#include "jfrog/entity.h"
#include "jfrog/input.h"

namespace game {

struct Game {
  bool is_paused;
  float time_left;

  entity::Entity* player;
  entity::Entity* cars;

  config::Config* config;
};

void initGame(Game& _game);
void deinitGame(Game& _game);
void restartGame(Game& _game);
void doPlayerMovement(Game& _game, input::Input& input);

}  // namespace game

#endif
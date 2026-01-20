#ifndef JFROG_ENTITY_H
#define JFROG_ENTITY_H

#include "jfrog/config.h"

namespace entity {

struct Entity {
  float pos_x, pos_y;
  int width, height;
  float speed;
  int color;
  char* sprite;
};

void initPlayer(Entity& _player, config::Config& _config);
void deinitEntity(Entity& _entity);
void printEntity(Entity& _entity, WINDOW* _window);

}  // namespace entity

#endif
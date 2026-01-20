#ifndef JFROG_ENTITY_H
#define JFROG_ENTITY_H

#include "jfrog/config.h"

typedef struct Entity
{
    float pos_x, pos_y;
    int width, height;
    float speed;
    int color;
    char *sprite;
} Entity;

// void entityInitPlayer(Entity* _player, Config* _config);
// void entityDeinit(Entity* _entity);
// void entityPrint(Entity* _entity, WINDOW* _window);

#endif
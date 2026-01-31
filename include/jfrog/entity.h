#ifndef JFROG_ENTITY_H
#define JFROG_ENTITY_H

#include "jfrog/config.h"
#include "jfrog/render.h"

typedef struct Entity
{
    float pos_x, pos_y;
    unsigned int width, height;
    float speed;
    char *sprite;
} Entity;

void entityInitPlayer(Entity *_player);
void entityDeinit(Entity *_entity);
void entityPrint(Entity *_entity, Screen *const _screen);

#endif
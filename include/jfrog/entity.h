#ifndef JFROG_ENTITY_H
#define JFROG_ENTITY_H

#include <stdbool.h>

#include "jfrog/config.h"
#include "jfrog/render.h"

typedef struct Entity
{
    float pos_x, pos_y;
    unsigned int width, height;
    char *sprite;
    bool active;
} Entity;

typedef struct CarRow
{
    float pos_y;
    unsigned int concurent_cars;
    bool active;
    Entity cars[10];
} CarRow;

void entityInitPlayer(Entity *_player);
void entityInitCar(Entity *_car);
void entityDeinit(Entity *_entity);
void entityPrint(Entity *_entity, Screen *const _screen);
int entityCheckCollision(Entity *_entity_a, Entity *_entity_b);

void entityInitCarRow(CarRow *_row);
void entityDeinitCarRow(CarRow *_row);

#endif
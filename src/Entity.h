#pragma once

#include <SDL.h>

class Entity
{
    unsigned int pos_x, pos_y;
    SDL_Texture* texture;

public:
    Entity();

    unsigned int& getPosX();
    unsigned int& getPosY();
};
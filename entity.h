#pragma once

#include "SDL.h"
#include "SDL_main.h"

#define ENTITY_ANIMATION_FRAMES 8

class Entity
{
    enum Direction
    {
        right,
        left
    };
    uint8_t visible;
    int animation, scale, width, height;
    Direction direction;
    SDL_Texture *sprites[ENTITY_ANIMATION_FRAMES];

protected:
    double x_speed, y_speed;
    double x_pos, y_pos;

public:
    void setAnimationSprite(unsigned int frame, const char filename[]);
    void render();
    void setScale(const int scale);
    void calculateMovement();
    void setXY(int x, int y);
    void show();
    void hide();

    Entity();
    ~Entity();
};

void initPlayer();
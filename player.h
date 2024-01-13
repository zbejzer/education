#pragma once
#include "entity.h"

class Player : public Entity
{
    int max_speed, accel, x_input_accel, y_input_accel;
    uint8_t isFalling();

    void doJump();

public:

    void handleInput();
    void handleMovement();
    void setMaxSpeed(int max_speed);
    void setAccel(int accel);

    Player();
};

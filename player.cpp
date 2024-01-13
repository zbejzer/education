#include "player.h"

#include "defs.h"
#include "common.h"

uint8_t Player::isFalling()
{
    return 0;
}

void Player::doJump()
{
}

void Player::handleInput()
{
    x_input_accel = 0;
    y_input_accel = 0;

    if (app.controls.up)
    {
        y_input_accel -= accel;
    }
    if (app.controls.down)
    {
        y_input_accel += accel;
    }
    if (app.controls.right)
    {
        x_input_accel += accel;
    }
    if (app.controls.left)
    {
        x_input_accel -= accel;
    }
    if (app.controls.space)
    {
        doJump();
    }

    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Calculated player input accel: (%d,%d)", x_input_accel, y_input_accel);
}

void Player::handleMovement()
{
    double total_max_speed = max_speed * BASE_GAME_UNIT * BASE_SPEED_FACTOR;

    x_speed += BASE_GAME_UNIT * x_input_accel * app.delta;
    y_speed += BASE_GAME_UNIT * y_input_accel * app.delta;

    if (x_input_accel == 0)
    {
        x_speed = 0;
    }

    if (y_input_accel == 0)
    {
        y_speed = 0;
    }

    // TODO:
    // handle falling
    if (isFalling())
    {
    }

    if (x_speed > total_max_speed)
    {
        x_speed = total_max_speed;
    }
    if (-1 * x_speed > total_max_speed)
    {
        x_speed = -1 * total_max_speed;
    }

    if (y_speed > total_max_speed)
    {
        y_speed = total_max_speed;
    }
    if (-1 * y_speed > total_max_speed)
    {
        y_speed = -1 * total_max_speed;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Calculated player speed: (%f,%f)", x_speed, y_speed);
}

void Player::setMaxSpeed(int max_speed)
{
    this->max_speed = max_speed;
}

void Player::setAccel(int accel)
{
    this->accel = accel;
}

Player::Player() 
	: max_speed{1}
    , accel{1}
    , x_input_accel{0}
    , y_input_accel{0}
{
}

#include "entity.h"

#include"SDL.h"
#include"SDL_main.h"

#include "common.h"
#include "draw.h"
#include "defs.h"

void Entity::setAnimationSprite(unsigned int frame, const char filename[])
{
    if (frame < ENTITY_ANIMATION_FRAMES)
    {
        sprites[frame] = loadTexture(filename);
    }
    else
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "Unable to add animation %s at frame %d. Frame out of range.", filename, frame);
    }
}

void Entity::render()
{
    SDL_RendererFlip flip;
    SDL_Rect dest;

    SDL_QueryTexture(sprites[animation], NULL, NULL, &dest.w, &dest.h);
    dest.x = (int)x_pos;
    dest.y = (int)y_pos;
    dest.w *= scale;
    dest.h *= scale;

    width = dest.w;
    height = dest.h;

    if (direction == Direction::right)
    {
        flip = SDL_FLIP_NONE;
    }
    else
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (visible)
    {
        SDL_RenderCopyEx(app.renderer, sprites[animation], NULL, &dest, 0, NULL, flip);
    }
}

void Entity::setScale(const int scale)
{
    this->scale = scale;
}

void Entity::show()
{
    visible = 1;
}

void Entity::hide()
{
    visible = 0;
}

Entity::Entity()
    : visible{0}
    , animation{0}
    , scale{1}
    , width{0}
    , height{0}
    , x_speed{0}
    , y_speed{0}
    , x_pos{0}
    , y_pos{0}
    , direction{Direction::right}
{
    for (size_t i = 0; i < ENTITY_ANIMATION_FRAMES; i++)
    {
        sprites[i] = NULL;
    }
}

Entity::~Entity()
{
    for (size_t i = 0; i < ENTITY_ANIMATION_FRAMES; i++)
    {
        if (sprites[i] != NULL)
        {
            SDL_DestroyTexture(sprites[i]);
        }
    }
}

// TODO:
// change order of evaluation
void Entity::calculateMovement()
{
    if (x_pos >= 0 && x_pos <= SCREEN_WIDTH)
    {
        x_pos += BASE_GAME_UNIT * x_speed * app.delta;
    }

    if (y_pos >= 0 && y_pos <= SCREEN_WIDTH)
    {
        y_pos += BASE_GAME_UNIT * y_speed * app.delta;
    }

    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Calculated entity location: (%f,%f)", x_pos, y_pos);
}

void Entity::setXY(int x, int y)
{
    x_pos = (double)x;
    y_pos = (double)y;
}

enum PlayerAnimations
{
    stand,
    walk1,
    walk2,
    jump
};

void initPlayer()
{
    player.setAnimationSprite(PlayerAnimations::stand, "./assets/mario/mario-stand.bmp");
    player.setScale(2);
    player.setXY(50, 50);
    player.setAccel(10);
    player.setMaxSpeed(10);
    game.start();
}
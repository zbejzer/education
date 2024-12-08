#ifndef GAME_H
#define GAME_H

#include "entity.hpp"
#include "config.hpp"

namespace game
{

struct Game
{
    bool is_paused;
    bool pressed_keys[4];

    float time_left;

    entity::Entity* player;
    entity::Entity* cars;

    config::Config* config;
};

void initGame(Game &_game);
void deinitGame(Game &_game);
void restartGame(Game &_game);

void doPlayerMovement(Game &_game);

} // namespace game

#endif
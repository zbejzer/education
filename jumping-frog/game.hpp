#ifndef GAME_H
#define GAME_H

#include "config.hpp"
#include "entity.hpp"
#include "input.hpp"

namespace game
{

struct Game
{
    bool is_paused;
    float time_left;

    entity::Entity *player;
    entity::Entity *cars;

    config::Config *config;
};

void initGame(Game &_game);
void deinitGame(Game &_game);
void restartGame(Game &_game);
void doPlayerMovement(Game &_game, input::Input &input);

} // namespace game

#endif
#include "game.hpp"

#include "config.hpp"
#include "entity.hpp"
#include "app.hpp"

namespace game
{
    
void initGame(Game &_game)
{
    _game.is_paused = true;

    _game.time_left = _game.config->time_limit;
    _game.player = new entity::Entity;
    _game.cars = new entity::Entity[_game.config->cars_count];

    for (size_t i = 0; i < 4; i++)
    {
        _game.pressed_keys[i] = false;
    }

    entity::initPlayer(*_game.player, *_game.config);
}

void deinitGame(Game &_game)
{
    entity::deinitEntity(*_game.player);

    // for (size_t i = 0; i < _game.config->cars_count; i++)
    // {
    //     entity::deinitEntity(_game.cars[i]);
    // }
    
    delete _game.player;
    delete _game.cars;
}

void restartGame(Game &_game)
{
    _game.is_paused = false;
    _game.time_left = _game.config->time_limit;
}

void doPlayerMovement(Game &_game)
{
    const config::Config config = *_game.config;

    entity::Entity &player = *_game.player; 

    if (_game.pressed_keys[0]) // W
    {
        player.pos_y -= player.speed * app::TICK_DURATION;
    }
    if (_game.pressed_keys[1]) // S
    {
        player.pos_y += player.speed * app::TICK_DURATION;
    }
    if (_game.pressed_keys[2]) // A
    {
        player.pos_x -= player.speed * app::TICK_DURATION;
    }
    if (_game.pressed_keys[3]) // D
    {
        player.pos_x += player.speed * app::TICK_DURATION;
    }
    
    // check for out of bounds position
    if (player.pos_x + float(player.width) > float(config.game_max_x))
    {
        player.pos_x = float(config.game_max_x - player.width);
    } else if (player.pos_x < float(config.game_min_x))
    {
        player.pos_x = float(config.game_min_x);
    }
    if (player.pos_y + float(player.height) > float(config.game_max_y))
    {
        player.pos_y = float(config.game_max_y - player.height);
    } else if (player.pos_y < float(config.game_min_y))
    {
        player.pos_y = float(config.game_min_y);
    }
}

} // namespace game
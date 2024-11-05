#ifndef PLAYER_H
#define PLAYER_H

namespace player
{

struct Player
{
    float pos_x, pos_y;
};

void initPlayer(Player &_player);

} // namespace player

#endif
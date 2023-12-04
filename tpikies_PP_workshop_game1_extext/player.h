#pragma once

struct Player
{
    unsigned int pos;
    unsigned int num;
    unsigned int passedStartSeq;
    unsigned char isInactive;
    unsigned char isStarted;
};

void initPlayer(Player *_player, unsigned int _num);
void checkPlayerStartSequence(Player *_player, unsigned int _gameStartSeq[], unsigned int _moveValue);
unsigned char canPlayerStart(Player *_player, unsigned int _gameStartSeq[]);
void startAllPlayers(Player _players[]);
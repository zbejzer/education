#pragma once

struct Player
{
    int pos;
    int num;
    unsigned int passedStartSeq;
    int isInactive;
    int isStarted;
};

void initPlayer(Player *_player, int _num);
void checkPlayerStartSequence(Player *_player, unsigned int _gameStartSeq[], int _moveValue);
int canPlayerStart(Player *_player, unsigned int _gameStartSeq[]);
void startAllPlayers(Player _players[]);
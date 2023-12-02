#pragma once

#include "constants.h"
#include "player.h"
#include "mines.h"
#include "walls.h"

struct Game
{
    int end;
    int player;
    unsigned int boardSize;
    unsigned int startSeq[MAX_START_SEQUENCE];
    Mine mines[MAX_MINE_COUNT];
    Wall walls[MAX_WALL_COUNT];
};

void initPlayer(Player *_player, int _num);
void initGame(Game *_game);
void handleVictory(Game *_game, Player _player[]);
void handleMove(Game *_game, Player *_player, int _moveValue);
void handlePrint(Player _player[], char _arg);
void handleLasso(Player *_playerCurrent, Player *_playerTarget);
void handleMines(Mine _mines[], Player *_player);
int getNextPlayer(Player players[], unsigned int currentPlayerID);
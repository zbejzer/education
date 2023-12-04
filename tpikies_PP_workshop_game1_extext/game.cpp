#include <iostream>
#include <algorithm>

#include "game.h"

using namespace std;

void initGame(Game *_game)
{
    _game->end = 0;
    _game->player = -1; // preparation for the first game round

    for (int i = 0; i < MAX_START_SEQUENCE; i++)
    {
        _game->startSeq[i] = 0;
    }

    // Default values
    _game->startSeq[0] = 1;
    _game->startSeq[1] = 6;

    for (int i = 0; i < MAX_MINE_COUNT; i++)
    {
        _game->mines[i].pos = 0;
        _game->mines[i].bonusMove = 0;
    }

    for (int i = 0; i < MAX_WALL_COUNT; i++)
    {
        _game->walls[i].pos = 0;
        _game->walls[i].height = 0;
    }
}

void handleVictory(Game *_game, Player _player[])
{
    unsigned int leftPlayers = PLAYER_COUNT;

    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        if (_player[i].pos >= _game->boardSize)
        {
            cout << "P" << i + 1 << " won" << endl;
            _game->end = 1;
        }
        if (_player[i].isInactive)
        {
            leftPlayers--;
        }
    }

    if (leftPlayers == 0)
    {
        cout << "DRAW" << endl;
        _game->end = 1;
    }
}

void handleMove(Game *_game, Player *_player, unsigned int _moveValue)
{
    const unsigned int endMovePlayerPosition = _player->pos + _moveValue;

    while (_player->pos < endMovePlayerPosition && getWallHeight(_game->walls, _player->pos) <= _moveValue)
    {
        _player->pos++;
    }
}

void handleLasso(Player *_playerCurrent, Player *_playerTarget)
{
    // reverse direction
    if (_playerTarget->pos < _playerCurrent->pos)
    {
        if ((_playerCurrent->pos - _playerTarget->pos) >= 2)
        {
            _playerTarget->pos++;
            _playerCurrent->pos--;
        }
    }
    else
    {
        if ((_playerTarget->pos - _playerCurrent->pos) >= 2)
        {
            _playerTarget->pos--;
            _playerCurrent->pos++;
        }
    }
}

void handleMines(Mine _mines[], Player *_player)
{
    int bonus_move = getMineBonusMove(_mines, _player->pos);

    if (bonus_move != 0)
    {
        unsigned int visited_fields[MAX_MINE_COUNT] = {0};
        visited_fields[0] = _player->pos;

        while ((bonus_move != 0) && (!_player->isInactive))
        {
            _player->pos = max(0, bonus_move + (int)_player->pos);

            for (int checked_field = 0; checked_field < MAX_MINE_COUNT; checked_field++)
            {
                if (visited_fields[checked_field] == _player->pos)
                {
                    _player->isInactive = 1;
                    cout << "P" << _player->num << " was defeated by mines" << endl;
                    break;
                }
                else if (visited_fields[checked_field] == 0)
                {
                    visited_fields[checked_field] = _player->pos;
                    break;
                }
            }

            bonus_move = getMineBonusMove(_mines, _player->pos);
        }
    }
}

int getNextPlayer(Player players[], unsigned int currentPlayerID)
{
    do
    {
        currentPlayerID++;
        if (currentPlayerID >= PLAYER_COUNT)
        {
            currentPlayerID = 0;
        }
    } while (players[currentPlayerID].isInactive);

    return currentPlayerID;
}
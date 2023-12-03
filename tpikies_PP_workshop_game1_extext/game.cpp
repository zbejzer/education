#include <iostream>

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

void handleMove(Game *_game, Player *_player, int _moveValue)
{
    int endMovePlayerPosition = _player->pos + _moveValue;

    while (_player->pos < endMovePlayerPosition && getWallHeight(_game->walls, _player->pos) <= _moveValue)
    {
        _player->pos++;
    }
}

void handleLasso(Player *_playerCurrent, Player *_playerTarget)
{
    int reverseDirection = (_playerTarget->pos < _playerCurrent->pos);

    if (reverseDirection)
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
    int bonusMove = getMineBonusMove(_mines, _player->pos);

    if (bonusMove != 0)
    {
        unsigned int visitedFields[MAX_MINE_COUNT] = {0};
        visitedFields[0] = _player->pos;

        while ((bonusMove != 0) && (!_player->isInactive))
        {
            _player->pos += bonusMove;

            if (_player->pos < 0)
            {
                _player->pos = 0;
            }

            for (int checkedField = 0; checkedField < MAX_MINE_COUNT; checkedField++)
            {
                if (visitedFields[checkedField] == _player->pos)
                {
                    _player->isInactive = 1;
                    cout << "P" << _player->num << " was defeated by mines" << endl;
                    break;
                }
                else if (visitedFields[checkedField] == 0)
                {
                    visitedFields[checkedField] = _player->pos;
                    break;
                }
            }

            bonusMove = getMineBonusMove(_mines, _player->pos);
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
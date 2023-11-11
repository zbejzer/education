#include <iostream>
#include <string>
#include "constans.h"
#include "mines.h"
#include "player.h"

using namespace std;

struct Game;
void initPlayer(Player *_player, int _num);
void initGame(Game *_game);
void handleVictory(Game *_game, Player _player[]);
void handleMove(Game *_game, Player *_player, int _moveValue);
void handlePrint(Game *_game, Player _player[], char _arg);
void handleLasso(Player *_playerCurrent, Player *_playerTarget);
void handleMines(Mine _mines[], Player *_player);
void nextPlayer(Game *_game, Player player[]);

struct Wall
{
    int height;
    unsigned int pos;
};

struct Game
{
    int end;
    int player;
    unsigned int boardSize;
    int wallSet;
    unsigned int wallFieldNumber;
    unsigned int wallHeight;
    unsigned int startSeq[MAX_START_SEQUENCE];
    Mine mines[MAX_MINE_COUNT];
};

void initGame(Game *_game)
{
    _game->end = 0;
    _game->player = -1; // preparation for the first game round
    _game->wallSet = 0;

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
    if (_game->wallSet)
    {
        if ((_player->pos <= _game->wallFieldNumber) && (_game->wallFieldNumber <= (_player->pos + _moveValue)))
        {
            if (_moveValue >= _game->wallHeight)
            {
                _player->pos += _moveValue;
            }
            else
            {
                _player->pos = _game->wallFieldNumber;
            }
        }
    }
    else
    {
        _player->pos += _moveValue;
    }
}

void handlePrint(Game *_game, Player _player[], char _arg)
{
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        if (_player[i].isInactive)
        {
            cout << "X ";
        }
        else
        {
            cout << _player[i].pos << " ";
        }
    }

    if (_arg == '1')
    {
        unsigned char States = 0;
        unsigned char diode = 128; // 0b10000000

        for (int i = 0; diode > 0; i++)
        {
            States = States | (diode * _player[i].isStarted);
            diode = (diode >> 1);
            States = States | (diode * (_player[i].pos % 2));
            diode = (diode >> 1);
        }

        for (unsigned int i = 0; i < 8; i++)
        {
            if (States & (1 << (7 - i)))
            {
                cout << 1;
            }
            else
            {
                cout << 0;
            }
        }
    }
    cout << endl;
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

            for (int i = 0; i < MAX_MINE_COUNT; i++)
            {
                if (visitedFields[i] == _player->pos)
                {
                    _player->isInactive = 1;
                    cout << "P" << _player->num << " was defeated by mines" << endl;
                    break;
                }
                else if (visitedFields[i] == 0)
                {
                    visitedFields[i] = _player->pos;
                    break;
                }
            }

            bonusMove = getMineBonusMove(_mines, _player->pos);
        }
    }
}

void nextPlayer(Game *_game, Player player[])
{
    do
    {
        _game->player++;
        if (_game->player >= PLAYER_COUNT)
        {
            _game->player = 0;
        }
    } while (player[_game->player].isInactive);
}

int main()
{
    string command;

    Game game;
    Player player[PLAYER_COUNT];

    initGame(&game);

    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        initPlayer(&player[i], i + 1);
    }

    do
    {
        cin >> command;

        if (command == "INIT")
        {
            cin >> game.boardSize;
        }
        else if (command == "INITSEQ")
        {
            int initSeqLength;
            cin >> initSeqLength;

            // Overwriting default start sequence
            game.startSeq[0] = 0;
            game.startSeq[1] = 0;

            for (int i = 0; i < initSeqLength; i++)
            {
                cin >> game.startSeq[i];
            }

            // No start requirements 
            if (initSeqLength == 0)
            {
                for (int i = 0; i < PLAYER_COUNT; i++)
                {
                    player[i].isStarted = 1;
                }
            }
        }
        else if (command == "MOVE")
        {
            unsigned int moveValue;
            cin >> moveValue;

            nextPlayer(&game, player);

            if (!player[game.player].isStarted)
            {
                checkPlayerStartSequence(&player[game.player], game.startSeq, moveValue);
                player[game.player].isStarted = canPlayerStart(&player[game.player], game.startSeq);
            }
            else
            {
                handleMove(&game, &player[game.player], moveValue);
                handleMines(game.mines, &player[game.player]);
            }
            handleVictory(&game, player);
        }
        else if (command == "ABORT")
        {
            cout << "ABORTED" << endl;
            game.end = 1;
        }
        else if (command == "PRINT")
        {
            // FOR 0 should print only positions. For 1 positions and diodes
            char arg;
            cin >> arg;

            handlePrint(&game, player, arg);
        }
        else if (command == "MINED")
        {
            unsigned int mineFieldNumber;
            int bonusMove;
            cin >> mineFieldNumber;
            cin >> bonusMove;

            addMine(game.mines, mineFieldNumber, bonusMove);
        }
        else if (command == "WALLED")
        {
            cin >> game.wallFieldNumber;
            cin >> game.wallHeight;
            game.wallSet = 1;
        }
        else if (command == "LASSO")
        {
            string targetPlayer;
            cin >> targetPlayer;
            int targetPlayerIndex = stoi(targetPlayer.substr(1, targetPlayer.size() - 1)) - 1;

            nextPlayer(&game, player);

            handleLasso(&player[game.player], &player[targetPlayerIndex]);
            handleMines(game.mines, &player[game.player]);
            handleMines(game.mines, &player[targetPlayerIndex]);
            handleVictory(&game, player);
        }
        else
        {
            cout << "BAD INPUT" << endl;
            game.end = 1;
        }
    } while (!game.end);

    return 0;
}
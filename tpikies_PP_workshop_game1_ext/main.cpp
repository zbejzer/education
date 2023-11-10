#include <iostream>
#include <string>

using namespace std;

const int PLAYER_COUNT = 4;
const int MAX_START_SEQUENCE = 10;

struct Player;
struct Game;
void initPlayer(Player *_player);
void initGame(Game *_game);
void handleVictory(Game *_game, Player _player[]);
void handlePlayerStart(Game *_game, Player *_player, int _moveValue);
void handleMove(Game *_game, Player *_player, int _moveValue);
void handlePrint(Game *_game, Player *_player, char _arg);
int hasPlayerStarted(Game *_game, Player *_player);

struct Player
{
    unsigned int pos;
    unsigned int startSeq[MAX_START_SEQUENCE];
};

struct Game
{
    int end;
    int player;
    unsigned int boardSize;
    unsigned int bonusMove;
    int mineSet;
    unsigned int mineFieldNumber;
    int wallSet;
    unsigned int wallFieldNumber;
    unsigned int wallHeight;
    unsigned int startSeq[MAX_START_SEQUENCE];
};

void initPlayer(Player *_player)
{
    _player->pos = 0;

    for (size_t i = 0; i < MAX_START_SEQUENCE; i++)
    {
        _player->startSeq[i] = 0;
    }
}

void initGame(Game *_game)
{
    _game->end = 0;
    _game->player = -1; // exception for the first game round
    _game->mineSet = 0;
    _game->wallSet = 0;

    for (size_t i = 0; i < MAX_START_SEQUENCE; i++)
    {
        _game->startSeq[i] = 0;
    }

    _game->startSeq[0] = 1;
    _game->startSeq[1] = 6;
}

void handleVictory(Game *_game, Player _player[])
{
    for (size_t i = 0; i < PLAYER_COUNT; i++)
    {
        if (_player[i].pos >= _game->boardSize)
        {
            cout << "P" << i + 1 << " won" << endl;
            _game->end = 1;
        }
    }
}

void handlePlayerStart(Game *_game, Player *_player, int _moveValue)
{
    int index = 0;

    while (_player->startSeq[index] == 1)
    {
        index++;
    }

    if (_game->startSeq[index] != 0)
    {
        if (_moveValue == _game->startSeq[index])
        {
            _player->startSeq[index] = 1;
        }
        else
        {
            index = 0;

            while (_game->startSeq[index] != 0)
            {
                _player->startSeq[index] = 0;
                index++;
            }
        }

        if (_moveValue == _game->startSeq[0])
        {
            _player->startSeq[0] = 1;
        }
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
    if (_game->mineSet && (_player->pos == _game->mineFieldNumber))
    {
        _player->pos += _game->bonusMove;
    }
}

void handlePrint(Game *_game, Player _player[], char _arg)
{
    for (size_t i = 0; i < PLAYER_COUNT; i++)
    {
        cout << _player[i].pos << " ";
    }

    if (_arg == '1')
    {
        unsigned char States = 0;
        unsigned char diode = 128; // 0b10000000

        for (size_t i = 0; diode > 0; i++)
        {
            States = States | (diode * hasPlayerStarted(_game, &_player[i]));
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

int hasPlayerStarted(Game *_game, Player *_player)
{
    int index = 0;

    while (_game->startSeq[index] != 0)
    {
        if (_player->startSeq[index] == 0)
        {
            return 0;
        }

        index++;
    }

    return 1;
}

int main()
{
    string command;

    Game game;
    Player player[PLAYER_COUNT];

    initGame(&game);

    for (size_t i = 0; i < PLAYER_COUNT; i++)
    {
        initPlayer(&player[i]);
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

            game.startSeq[0] = 0;
            game.startSeq[1] = 0;

            for (size_t i = 0; i < initSeqLength; i++)
            {
                cin >> game.startSeq[i];
            }
        }
        else if (command == "MOVE")
        {
            unsigned int moveValue;
            cin >> moveValue;

            game.player++;
            if (game.player >= PLAYER_COUNT)
            {
                game.player = 0;
            }

            if (!hasPlayerStarted(&game, &player[game.player]))
            {
                handlePlayerStart(&game, &player[game.player], moveValue);
            }
            else
            {
                handleMove(&game, &player[game.player], moveValue);
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
            cin >> game.mineFieldNumber;
            cin >> game.bonusMove;
            game.mineSet = 1;
            // if a player stand on mineFieldNumber, then she goes + bonusMove
        }
        else if (command == "WALLED")
        {
            cin >> game.wallFieldNumber;
            cin >> game.wallHeight;
            game.wallSet = 1;
        }
        else
        {
            cout << "BAD INPUT" << endl;
            game.end = 1;
        }
    } while (!game.end);

    return 0;
}
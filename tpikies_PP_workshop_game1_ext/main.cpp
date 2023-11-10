#include <iostream>
#include <string>

using namespace std;

const int PLAYER_COUNT = 4;

struct Player;
struct Game;
void initPlayer(Player *_player);
void initGame(Game *_game);
void handleVictory(Game *_game, Player _player[]);
void handlePlayerStart(Player *_player, int _moveValue);
void handleMove(Game *_game, Player *_player, int _moveValue);

struct Player
{
    int got1;
    int got6;
    unsigned int pos;
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
};

void initPlayer(Player *_player)
{
    _player->got1 = 0;
    _player->got6 = 0;
    _player->pos = 0;
}

void initGame(Game *_game)
{
    _game->end = 0;
    _game->player = -1; // exception for the first game round
    _game->mineSet = 0;
    _game->wallSet = 0;
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

void handlePlayerStart(Player *_player, int _moveValue)
{
    if (!_player->got1)
    {
        _player->got1 = (_moveValue == 1);
    }
    else if (!_player->got6)
    {
        if (_moveValue == 6)
        {
            _player->got6 = 1;
        }
        else
        {
            _player->got1 = (_moveValue == 1);
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
        else if (command == "MOVE")
        {
            unsigned int moveValue;
            cin >> moveValue;

            game.player++;
            if (game.player >= PLAYER_COUNT)
            {
                game.player = 0;
            }

            if (!(player[game.player].got1 && player[game.player].got6))
            {
                handlePlayerStart(&player[game.player], moveValue);
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
            unsigned char States = 0;
            cin >> arg;

            States = States | (0b10000000 * player[0].got6) | (0b00100000 * player[1].got6) |
                     (0b00001000 * player[2].got6) | (0b00000010 * player[3].got6);
            States = States | (0b01000000 * (player[0].pos % 2)) | (0b00010000 * (player[1].pos % 2)) |
                     (0b00000100 * (player[2].pos % 2)) | (0b00000001 * (player[3].pos % 2));

            cout << player[0].pos << " " << player[1].pos << " " << player[2].pos << " " << player[3].pos << " ";

            if (arg == '1')
            {
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
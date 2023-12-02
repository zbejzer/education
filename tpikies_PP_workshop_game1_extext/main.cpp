#include <iostream>
#include <string>
#include "constants.h"
#include "player.h"
#include "mines.h"
#include "walls.h"
#include "game.h"

using namespace std;

int main()
{
    string command;

    Game game;
    Player players[PLAYER_COUNT];

    initGame(&game);

    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        initPlayer(&players[i], i + 1);
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
                startAllPlayers(players);
            }
        }
        else if (command == "MOVE")
        {
            unsigned int moveValue;
            cin >> moveValue;

            game.player = getNextPlayer(players, game.player);

            if (!players[game.player].isStarted)
            {
                checkPlayerStartSequence(&players[game.player], game.startSeq, moveValue);
                players[game.player].isStarted = canPlayerStart(&players[game.player], game.startSeq);
            }
            else
            {
                handleMove(&game, &players[game.player], moveValue);
                handleMines(game.mines, &players[game.player]);
            }

            handleVictory(&game, players);
        }
        else if (command == "ABORT")
        {
            cout << "ABORTED" << endl;
            game.end = 1;
        }
        else if (command == "PRINT")
        {
            char arg;
            cin >> arg;

            handlePrint(players, arg);
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
            unsigned int wallFieldNumber;
            int wallHeight;

            cin >>wallFieldNumber;
            cin >> wallHeight;
            addWall(game.walls, wallFieldNumber, wallHeight);
        }
        else if (command == "LASSO")
        {
            string targetPlayer;
            cin >> targetPlayer;
            int targetPlayerIndex = stoi(targetPlayer.substr(1, targetPlayer.size() - 1)) - 1;

            game.player = getNextPlayer(players, game.player);

            handleLasso(&players[game.player], &players[targetPlayerIndex]);
            handleMines(game.mines, &players[game.player]);
            handleMines(game.mines, &players[targetPlayerIndex]);
            handleVictory(&game, players);
        }
        else
        {
            cout << "BAD INPUT" << endl;
            game.end = 1;
        }
    } while (!game.end);

    return 0;
}
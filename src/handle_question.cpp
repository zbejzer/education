#pragma once

#include <cstdio>
#include <cstring>

#include "board.hpp"
#include "handle_question.hpp"
#include "pawns.hpp"

void handleQuestion(const char *const question, Board &board)
{
    if (strcmp(question, "BOARD_SIZE") == 0)
    {
        printf("%d\n", board.size);
    }
    else if (strcmp(question, "PAWNS_NUMBER") == 0)
    {
        printf("%d\n", board.getPawnsCount());
    }
    else if (strcmp(question, "IS_BOARD_CORRECT") == 0)
    {
        if (board.isBoardCorrect())
        {
            fputs("YES\n", stdout);
        }
        else
        {
            fputs("NO\n", stdout);
        }
    }
    else if (strcmp(question, "IS_GAME_OVER") == 0)
    {
        if (board.isBoardCorrect())
        {
            switch (board.isGameOver())
            {
            case PawnColour::Red:
                fputs("YES RED\n", stdout);
                break;
            case PawnColour::Blue:
                fputs("YES BLUE\n", stdout);
                break;
            default:
                fputs("NO\n", stdout);
                break;
            }
        }
        else
        {
            fputs("NO\n", stdout);
        }
    }
    else if (strcmp(question, "IS_BOARD_POSSIBLE") == 0)
    {
        if (board.isBoardPossible())
        {
            fputs("YES\n", stdout);
        }
        else
        {
            fputs("NO\n", stdout);
        }
    }
    else if (strncmp(question, "CAN_", 4) == 0)
    {
        const char *adjusted_question = question + 4;
        unsigned char n_moves = 0;
        PawnColour colour = PawnColour::Empty;

        if (strncmp(adjusted_question, "RED", 3) == 0)
        {
            colour = PawnColour::Red;
            adjusted_question += 11;
        }
        else
        {
            colour = PawnColour::Blue;
            adjusted_question += 12;
        }
        n_moves = *adjusted_question - '0';

        if (n_moves > 1)
        {
            adjusted_question += 13;
        }
        else
        {
            adjusted_question += 12;
        }

        if (strncmp(adjusted_question, "NAIVE", 5) == 0)
        {
            if (board.canWinWithNaiveOpponent(colour, n_moves))
            {
                fputs("YES\n", stdout);
            }
            else
            {
                fputs("NO\n", stdout);
            }
        }
        else
        {
            if (board.canWinWithPerfectOpponent(colour, n_moves))
            {
                fputs("YES\n", stdout);
            }
            else
            {
                fputs("NO\n", stdout);
            }
        }
    }

    return;
}

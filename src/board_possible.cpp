#include "board.hpp"
#include "pawns.hpp"

bool Board::isLossInPreviousTurnPossible(const PawnColour pawn_colour)
{
    for (unsigned char i = 0; i < size * size; i++)
    {
        if ((*current_board)(i) == pawn_colour)
        {
            (*current_board)(i) = PawnColour::Empty;
            if (!isGameOver(pawn_colour))
            {
                (*current_board)(i) = pawn_colour;
                return true;
            }
            (*current_board)(i) = pawn_colour;
        }
    }

    return false;
}

bool Board::isBoardPossible()
{
    if (isBoardCorrect())
    {
        if (isGameOver(PawnColour::Red))
        {
            if (!isRedTurnNow())
            {
                current_board = &board_red;
                return isLossInPreviousTurnPossible(PawnColour::Red);
            }
            else
            {
                return false;
            }
        }
        else if (isGameOver(PawnColour::Blue))
        {
            if (isRedTurnNow())
            {
                current_board = &board_blue;
                return isLossInPreviousTurnPossible(PawnColour::Blue);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

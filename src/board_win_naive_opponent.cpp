#include "board.hpp"

#include "array_1D.hpp"
#include "pawns.hpp"
#include "stack.hpp"

bool Board::addPawnAndCheckForWin(const PawnColour target_pawn_colour, const unsigned char moves,
                                  const unsigned char start_col, const unsigned char start_row)
{
    if (moves > 0)
    {
        for (unsigned char col = start_col; col < size; col++)
        {
            for (unsigned char row = 0; row < size; row++)
            {
                if ((*current_board)(col, row) == PawnColour::Empty)
                {
                    (*current_board)(col, row) = target_pawn_colour;
                    // Start checking the next board at current position
                    if (addPawnAndCheckForWin(target_pawn_colour, moves - 1, col, row))
                    {
                        (*current_board)(col, row) = PawnColour::Empty;
                        return true;
                    }
                    (*current_board)(col, row) = PawnColour::Empty;
                }
            }
        }
    }

    // debugPrint();
    return isGameOverFast(target_pawn_colour);
}

bool Board::canWinWithNaiveOpponent(const PawnColour target_pawn_colour, const unsigned char moves)
{
    unsigned char total_moves_to_make = moves * 2;
    unsigned char requested_pawns_end_count = getPawnsCount(target_pawn_colour) + moves;

    if (isRedTurnNow() == (target_pawn_colour == PawnColour::Red))
    {
        total_moves_to_make -= 1;
    }

    if (!isBoardCorrect() || total_moves_to_make + getPawnsCount() > size * size || requested_pawns_end_count < size ||
        isGameOver() != PawnColour::Empty)
    {
        return false;
    }

    if (target_pawn_colour == PawnColour::Red)
    {
        current_board = &board_red;
    }
    else
    {
        current_board = &board_blue;
    }

    return addPawnAndCheckForWin(target_pawn_colour, moves, 0, 0);
}

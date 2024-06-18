#include "board.hpp"

#include "pawns.hpp"

bool Board::canWinWithPerfectOpponent(const PawnColour pawn_colour, const unsigned char moves) const
{
    /*unsigned char total_moves_to_make = moves * 2;
    unsigned char requested_pawn_count = 0;
    unsigned char total_end_pawns_count = 0;

    if (pawn_colour == PAWN_RED)
    {
        requested_pawn_count = red;
    }
    else {
        requested_pawn_count = blue;
    }

    if (isRedTurnNow() == (pawn_colour == PAWN_RED))
    {
        total_moves_to_make -= 1;
    }

    total_end_pawns_count = total_moves_to_make + red + blue;

    if (!isBoardCorrect() || total_end_pawns_count > size * size || requested_pawn_count + moves < size || isGameOver()
    != PAWN_EMPTY)
    {
        return false;
    }

    bool is_win_possible = false;
    Stack<Board> possible_boards;

    possible_boards.push(Board(*this));

    while (!possible_boards.empty() && possible_boards.top().getTotalPawnsCount() < total_end_pawns_count)
    {
        while (possible_boards.top().getTotalPawnsCount() + 1 < total_end_pawns_count)
        {
            Board current_board(possible_boards.top());
            possible_boards.pop();

            current_board.generatePossibleTurns(PAWNS_ORDER[current_board.getTotalPawnsCount() % 2], false,
    possible_boards);
        }

        Board current_board(possible_boards.top());
        possible_boards.pop();
        current_board.generatePossibleTurns(pawn_colour, true, possible_boards);
    }

    if (!possible_boards.empty() && possible_boards.top().getTotalPawnsCount() == total_end_pawns_count)
    {
        is_win_possible = true;
    }

    return is_win_possible;*/

    return false;
}

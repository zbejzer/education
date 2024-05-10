#include "board.hpp"

#include "stack.hpp"

bool Board::canWinWithNaiveOpponent(const unsigned char pawn_colour, const unsigned char moves) const
{
	unsigned char total_moves_to_make = moves * 2;
	unsigned char requested_pawns_end_count = getPawnsCount(pawn_colour) + moves;

	if (isRedTurnNow() == (pawn_colour == PAWN_RED))
	{
		total_moves_to_make -= 1;
	}

	if (!isBoardCorrect() || total_moves_to_make + getPawnsCount() > size * size || requested_pawns_end_count < size || isGameOver() != PAWN_EMPTY)
	{
		return false;
	}

	Stack<Board> possible_boards;

	possible_boards.push(Board(*this));

	while (!possible_boards.empty() && possible_boards.top().getPawnsCount(pawn_colour) < requested_pawns_end_count)
	{
		while (possible_boards.top().getPawnsCount(pawn_colour) + 1 < requested_pawns_end_count)
		{
			Board current_board(possible_boards.top());
			possible_boards.pop();

			current_board.generateAllPossibleTurns(pawn_colour, false, possible_boards);
		}

		Board current_board(possible_boards.top());
		possible_boards.pop();
		current_board.generateBestPossibleTurns(pawn_colour, possible_boards);

		while (!possible_boards.empty() && possible_boards.top().getPawnsCount(pawn_colour) == requested_pawns_end_count && !possible_boards.top().isGameOver(pawn_colour))
		{
			possible_boards.pop();
		}
	}

	if (!possible_boards.empty())
	{
		return true;
	}

	return false;
}

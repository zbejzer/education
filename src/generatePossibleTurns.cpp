#include "board.hpp"
#include "stack.hpp"
#include "utility.hpp"

void Board::generateBestPossibleTurns(const unsigned char pawn_colour, Stack<Board>& possible_turns) const
{
	static const char d_row[6] = { -1,  0, 1, -1, 1, 0 };
	static const char d_col[6] = { -1, -1, 0,  0, 1, 1 };
	bool** pawn_created = create2DArray<bool>(size, false);

	if (pawn_colour == PAWN_RED)
	{
		for (unsigned char row = 0; row < size; row++)
		{
			if (board[0][row] == PAWN_EMPTY)
			{
				Board new_board(*this);
				new_board.addPawn(pawn_colour, 0, row);
				pawn_created[0][row] = true;
				possible_turns.push(new_board);
			}
			if (board[size - 1][row] == PAWN_EMPTY)
			{
				Board new_board(*this);
				new_board.addPawn(pawn_colour, size - 1, row);
				pawn_created[size - 1][row] = true;
				possible_turns.push(new_board);
			}
		}
	}
	else
	{
		for (unsigned char col = 0; col < size; col++)
		{
			if (board[col][0] == PAWN_EMPTY)
			{
				Board new_board(*this);
				new_board.addPawn(pawn_colour, col, 0);
				pawn_created[col][0] = true;
				possible_turns.push(new_board);
			}
			if (board[col][size - 1] == PAWN_EMPTY)
			{
				Board new_board(*this);
				new_board.addPawn(pawn_colour, col, size - 1);
				pawn_created[col][size - 1] = true;
				possible_turns.push(new_board);
			}
		}
	}

	short test_col = 0, test_row = 0;

	for (unsigned char col = 0; col < size; col++)
	{
		for (unsigned char row = 0; row < size; row++)
		{
			if (board[col][row] == pawn_colour)
			{
				for (unsigned char i = 0; i < 6; i++)
				{
					test_col = col + d_col[i];
					test_row = row + d_row[i];

					if (posInRange(test_col, test_row) && board[test_col][test_row] == PAWN_EMPTY && !pawn_created[test_col][test_row])
					{
						Board new_board(*this);
						new_board.addPawn(pawn_colour, static_cast<unsigned char>(test_col), static_cast<unsigned char>(test_row));
						pawn_created[test_col][test_row] = true;
						possible_turns.push(new_board);
					}
				}
			}
		}
	}
}

void Board::generateAllPossibleTurns(const unsigned char pawn_colour, const bool should_win, Stack<Board>& possible_turns) const
{
	for (unsigned char col = 0; col < size; col++)
	{
		for (unsigned char row = 0; row < size; row++)
		{
			if (board[col][row] == PAWN_EMPTY)
			{
				Board new_board(*this);
				new_board.addPawn(pawn_colour, static_cast<unsigned char>(col), static_cast<unsigned char>(row));
				if (new_board.isGameOver(pawn_colour) == should_win)
				{
					possible_turns.push(new_board);
				}
			}
		}
	}
}

#include "board.hpp"
#include "pawns.hpp"
#include "stack.hpp"
#include "array_2D.hpp"

bool Board::gameOverDfs(PawnColour target_pawn_colour, const unsigned char col, const unsigned char row) const
{
	static const char d_row[6] = { -1,  0, 1, -1, 1, 0 };
	static const char d_col[6] = { -1, -1, 0,  0, 1, 1 };

	char test_row, test_col;

	visited_fields(col, row) = true;

	if (col == size - 1)
	{
		return true;
	}

	for (unsigned char i = 0; i < 6; i++)
	{
		test_col = col + d_col[i];
		test_row = row + d_row[i];
		
		if (posInRange(test_col, test_row) && (*current_board)(test_col, test_row) == target_pawn_colour && !visited_fields(test_col, test_row))
		{
			if (gameOverDfs(target_pawn_colour, test_col, test_row))
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::isGameOverFast(const PawnColour target_pawn_colour)
{
	visited_fields.zero();
	for (unsigned char row = 0; row < size; row++)
	{
		if ((*current_board)(0, row) == target_pawn_colour && !visited_fields(0, row))
		{
			if (gameOverDfs(target_pawn_colour, 0, row))
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::isGameOver(const PawnColour target_pawn_colour)
{
	if (getPawnsCount(target_pawn_colour) < size)
	{
		return false;
	}

	bool exists_1 = false, exists_2 = false;

	if (target_pawn_colour == PawnColour::Red)
	{
		current_board = &board_red;
	}
	else
	{
		current_board = &board_blue;
	}

	//debugPrint();

	// Testing for pawns placed at edges
	for (unsigned char i = 0; i < size; i++)
	{
		if ((*current_board)(0, i) == target_pawn_colour)
		{
			exists_1 = true;
			break;
		}
	}
	for (unsigned char i = 0; i < size; i++)
	{
		if ((*current_board)(size - 1, i) == target_pawn_colour)
		{
			exists_2 = true;
			break;
		}
	}
	if (!(exists_1 && exists_2))
	{
		return false;
	}

	return isGameOverFast(target_pawn_colour);
}

PawnColour Board::isGameOver()
{
	static const PawnColour target_pawn[2] = { PawnColour::Red, PawnColour::Blue };

	for (unsigned char pawn_i = 0; pawn_i < 2; pawn_i++)
	{
		if (isGameOver(target_pawn[pawn_i]))
		{
			return target_pawn[pawn_i];
		}
	}

	return PawnColour::Empty;
}
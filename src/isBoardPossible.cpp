#include "board.hpp"

bool Board::isLossInPreviousTurnPossible(const unsigned char pawn_colour) const
{
	for (unsigned char col = 0; col < size; col++)
	{
		for (unsigned char row = 0; row < size; row++)
		{
			if(board[col][row] == pawn_colour)
			{
				board[col][row] = PAWN_EMPTY;
				if (!isGameOver(pawn_colour))
				{
					board[col][row] = pawn_colour;
					return true;
				}
				board[col][row] = pawn_colour;
			}
		}
	}

	return false;
}

bool Board::isBoardPossible() const
{
	if (isBoardCorrect())
	{
		if (isGameOver(PAWN_RED))
		{
			if (!isRedTurnNow())
			{
				return isLossInPreviousTurnPossible(PAWN_RED);
			}
			else 
			{
				return false;
			}
		}
		else if (isGameOver(PAWN_BLUE))
		{
			if (isRedTurnNow())
			{
				return isLossInPreviousTurnPossible(PAWN_BLUE);
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

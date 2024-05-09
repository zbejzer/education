#include "board.hpp"

#include <cstring>

void Board::handleQuestion(char* question) const
{
	if (question[0] == '\0' || question[0] == ' ')
	{
		return;
	}
	else if (strcmp(question, "BOARD_SIZE") == 0)
	{
		printf("%d\n", size);
	}
	else if (strcmp(question, "PAWNS_NUMBER") == 0)
	{
		printf("%d\n\n", red + blue);
	}
	else if (strcmp(question, "IS_BOARD_CORRECT") == 0)
	{
		if (isBoardCorrect())
		{
			printf("YES\n\n");
		}
		else
		{
			printf("NO\n\n");
		}
	}
	else if (strcmp(question, "IS_GAME_OVER") == 0)
	{
		if (isBoardCorrect())
		{
			switch (isGameOver())
			{
			case PAWN_RED:
				printf("YES RED\n\n");
				break;
			case PAWN_BLUE:
				printf("YES BLUE\n\n");
				break;
			default:
				printf("NO\n\n");
				break;
			}
		}
		else
		{
			printf("NO\n\n");
		}
	}
	else if (strcmp(question, "IS_BOARD_POSSIBLE") == 0)
	{
		if (isBoardPossible())
		{
			printf("YES\n\n");
		}
		else
		{
			printf("NO\n\n");
		}
	}
	else if (strncmp(question, "CAN_", 4) == 0)
	{
		char* adjusted_question = question + 4;
		unsigned char n_moves = 0;
		unsigned char colour = 0;

		if (strncmp(adjusted_question, "RED", 3) == 0)
		{
			colour = PAWN_RED;
			adjusted_question += 11;
		}
		else
		{
			colour = PAWN_BLUE;
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
			if (canWinWithNaiveOpponent(colour, n_moves))
			{
				printf("YES\n\n");
			}
			else
			{
				printf("NO\n\n");
			}
		}
		else
		{
			if (canWinWithPerfectOpponent(colour, n_moves))
			{
				printf("YES\n\n");
			}
			else
			{
				printf("NO\n\n");
			}
		}
	}
}

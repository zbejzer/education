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
		if (isBoardPossible())
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
		if (isBoardPossible())
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
}

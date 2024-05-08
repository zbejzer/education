#include "board.hpp"

#include <cstdio>
#include <cstring>

Board::Board()
	: board(nullptr)
	, size(0)
	, red(0)
	, blue(0)
{
}

Board::~Board()
{
	if (board != nullptr)
	{
		destroyBoard();
	}
}

void Board::setSize(const unsigned char& size)
{
	this->size = size;
}

void Board::createBoard()
{
	board = new unsigned char*[size];
	for (size_t i = 0; i < size; i++)
	{
		board[i] = new unsigned char [size];
	}
}

void Board::destroyBoard()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] board[i];
	}
	delete[] board;

	board = nullptr;
}

void Board::handleQuestion(char* question)
{
	if (strcmp(question, "BOARD_SIZE"))
	{
		printf("%d\n", size);
	}
	else if (strcmp(question, "PAWNS_NUMBER"))
	{
		printf("%d\n", red + blue);
	}
	else if (strcmp(question, "IS_BOARD_CORRECT"))
	{
		if (isBoardCorrect())
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
}

bool Board::isBoardCorrect()
{
	return (red == blue + 1) || (red == blue);
}

void Board::debugPrint()
{
	for (size_t row = 0; row < size + 1; row++)
	{
		for (size_t col = 0; col < size + 1; col++) {
			if (row == 0)
			{
				printf("%-3d", static_cast<int>(col));
			}
			else if (col == 0)
			{
				printf("%-3d", static_cast<int>(row));
			}
			else
			{
				printf("%-3c", board[col - 1][row - 1]);
			}
		}
		printf("\n");
	}
}

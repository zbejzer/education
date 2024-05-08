#include "board.hpp"

#include <cstdio>
#include <cstring>
#include <ostream>

bool Board::posInRange(short col, short row) const
{
	return col >= 0 && row >= 0 && col < size && row < size;
}

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

void Board::setSize(const unsigned char size)
{
	this->size = size;
}

void Board::createBoard()
{
	board = new unsigned char* [size];
	for (unsigned char i = 0; i < size; i++)
	{
		board[i] = new unsigned char[size];
	}
}

void Board::destroyBoard(unsigned char** board) const
{
	for (unsigned char i = 0; i < size; i++)
	{
		delete[] board[i];
	}
	delete[] board;

	board = nullptr;
}

void Board::destroyBoard()
{
	destroyBoard(this->board);
}

unsigned char** Board::createAdjustedBoard(const unsigned char pawn_colour) const
{
	unsigned char** new_board = new unsigned char* [size];
	for (unsigned char i = 0; i < size; i++)
	{
		new_board[i] = new unsigned char[size];
	}

	if (pawn_colour == PAWN_RED)
	{
		for (unsigned char row = 0; row < size; row++)
		{
			for (unsigned char col = 0; col < size; col++)
			{
				new_board[col][row] = board[col][row];
			}
		}
	}
	else
	{
		for (unsigned char row = 0; row < size; row++)
		{
			for (unsigned char col = 0; col < size; col++)
			{
				new_board[col][row] = board[row][col];
			}
		}
	}

	return new_board;
}

void Board::handleQuestion(char* question)
{
	if (strcmp(question, "BOARD_SIZE") == 0)
	{
		printf("%d\n", size);
	}
	else if (strcmp(question, "PAWNS_NUMBER") == 0)
	{
		printf("%d\n", red + blue);
	}
	else if (strcmp(question, "IS_BOARD_CORRECT") == 0)
	{
		if ((red == blue + 1) || (red == blue))
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	else if (strcmp(question, "IS_GAME_OVER") == 0)
	{
		switch (isGameOver())
		{
		case PAWN_RED:
			printf("YES RED\n");
			break;
		case PAWN_BLUE:
			printf("YES BLUE\n");
			break;
		default:
			printf("NO\n");
			break;
		}
	}
}

void Board::debugPrint(unsigned char** board) const
{
	for (unsigned char row = 0; row < size + 1; row++)
	{
		for (unsigned char col = 0; col < size + 1; col++) {
			if (row == 0 && col > 0)
			{
				printf("%-3d", static_cast<int>(col - 1));
			}
			else if (col == 0 && row > 0)
			{
				printf("%-3d", static_cast<int>(row - 1));
			}
			else if (col > 0 && row > 0)
			{
				char pawn = ' ';
				if (board[col - 1][row - 1] == PAWN_RED)
				{
					pawn = 'R';
				}
				else if (board[col - 1][row - 1] == PAWN_BLUE)
				{
					pawn = 'B';
				}
				printf("%-3c", pawn);
			}
			else
			{
				printf("%-3c", ' ');
			}
		}
		printf("\n");
	}
}

void Board::debugPrint() const
{
	debugPrint(this->board);
}

Pos::Pos() : col(0), row(0)
{
}

Pos::Pos(unsigned char col, unsigned char row) : col(col), row(row)
{
}

std::ostream& operator<<(std::ostream& os, const Pos& pos)
{
	char buf[32];
	buf[0] = '\0';

	static_cast<void>(sprintf_s(buf, "(%u , %u)", pos.col, pos.row));
	os << buf;
	return os;
}

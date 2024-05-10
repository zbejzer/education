#include "board.hpp"

#include <cstdio>
#include <ostream>

#include "utility.hpp"

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

Board::Board(const Board& other)
	: size(other.size)
	, red(other.red)
	, blue(other.blue)
{
	board = createCopy2DArray<unsigned char>(other.board, size);
}

Board::~Board()
{
	destroy2DArray<unsigned char>(board, size);
}

void Board::setSize(const unsigned char size)
{
	this->size = size;
}

unsigned char Board::getPawnsCount() const
{
	return red + blue;
}

unsigned char Board::getPawnsCount(const unsigned char pawn_colour) const
{
	if (pawn_colour == PAWN_RED)
	{
		return red;
	}
	else if (pawn_colour == PAWN_BLUE)
	{
		return blue;
	}

	return size*size - (blue + red);
}

void Board::addPawn(const unsigned char pawn_colour, const unsigned char col, const unsigned char row)
{
	if (pawn_colour == PAWN_RED)
	{
		red++;
	}
	else if (pawn_colour == PAWN_BLUE)
	{
		blue++;
	}

	board[col][row] = pawn_colour;
}

unsigned char** Board::createAdjustedBoard(const unsigned char pawn_colour) const
{
	unsigned char** new_board = create2DArray<unsigned char>(size);

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

unsigned char Board::isRedTurnNow() const
{
	return red == blue;
}

bool Board::isBoardCorrect() const
{
	return (red == blue + 1) || (red == blue);
}

void Board::debugPrint() const
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
	for (unsigned char col = 0; col < size + 1; col++)
	{
		printf("===");
	}
	printf("\n");
}

Board& Board::operator=(Board other)
{
	using std::swap;
	swap(red, other.red);
	swap(blue, other.blue);
	swap(size, other.size);
	swap(board, other.board);

	return *this;
}

Pos::Pos() : col(0), row(0)
{
}

Pos::Pos(unsigned char col, unsigned char row) : col(col), row(row)
{
}

std::ostream& operator<<(std::ostream& os, const Pos& pos)
{
	char buf[32] = "";

	static_cast<void>(sprintf_s(buf, "(%u , %u)", pos.col, pos.row));
	os << buf;
	return os;
}

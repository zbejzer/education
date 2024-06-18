#include <cstdio>
#include <cstdlib>
#include <ostream>

#include "board.hpp"

#include "pawns.hpp"
#include "array_2D.hpp"

Array2D<PawnColour> Board::board_red(Board::MAX_BOARD_SIZE);
Array2D<PawnColour> Board::board_blue(Board::MAX_BOARD_SIZE);
Array2D<bool> Board::visited_fields(Board::MAX_BOARD_SIZE);

bool Board::posInRange(short col, short row) const
{
	return col >= 0 && row >= 0 && col < size && row < size;
}

Board::Board()
	: size(0)
	, red(0)
	, blue(0)
	, current_board(&Board::board_red)
{
}

Board::Board(const Board& other)
	: size(other.size)
	, red(other.red)
	, blue(other.blue)
{
}

Board::~Board()
{
}

void Board::setSize(const unsigned char size)
{
	this->size = size;
}

unsigned char Board::getPawnsCount() const
{
	return red + blue;
}

unsigned char Board::getPawnsCount(const PawnColour pawn_colour) const
{
	if (pawn_colour == PawnColour::Red)
	{
		return red;
	}
	else if (pawn_colour == PawnColour::Blue)
	{
		return blue;
	}

	return size * size - (blue + red);
}

void Board::addPawn(const PawnColour pawn_colour, const unsigned char col, const unsigned char row)
{
	if (pawn_colour == PawnColour::Red)
	{
		red++;
	}
	else if (pawn_colour == PawnColour::Blue)
	{
		blue++;
	}

	board_red(col, row) = pawn_colour;
}

void Board::updateBlueBoard()
{
	for (unsigned char row = 0; row < size; row++)
	{
		for (unsigned char col = 0; col < size; col++)
		{
			board_blue(col, row) = board_red(row, col);
		}
	}
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
				if ((*current_board)(col - 1, row - 1) == PawnColour::Red)
				{
					pawn = 'R';
				}
				else if ((*current_board)(col - 1, row - 1) == PawnColour::Blue)
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
	swap(board_red, other.board_red);
	swap(board_blue, other.board_blue);
	swap(current_board, other.current_board);
	swap(visited_fields, other.visited_fields);

	return *this;
}
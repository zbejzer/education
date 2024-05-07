#pragma once

#define PAWN_EMPTY 0
#define PAWN_RED 1
#define PAWN_BLUE 2

class Board
{
	unsigned char** board;
	unsigned char size;

public:
	Board();
	void setSize(const unsigned char& size);
	void createBoard();
	void destroyBoard();
};


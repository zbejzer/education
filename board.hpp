#pragma once

#include <iostream>

#define PAWN_EMPTY 0
#define PAWN_RED 1
#define PAWN_BLUE 2

struct Pos
{
	unsigned char col, row;
	Pos();
	Pos(unsigned char, unsigned char);

	friend std::ostream& operator<<(std::ostream& os, const Pos& pos);
};

class Board
{
	bool posInRange(short col, short row) const;
public:
	unsigned char** board;
	unsigned char size;
	unsigned char red, blue;

	Board();
	~Board();
	void setSize(const unsigned char size);
	void createBoard();
	void destroyBoard(unsigned char** board);
	void destroyBoard();
	unsigned char** createAdjustedBoard(const unsigned char pawn_color) const;
	void handleQuestion(char* question);
	unsigned char isGameOver();
	void debugPrint(unsigned char** board);
	void debugPrint();
};

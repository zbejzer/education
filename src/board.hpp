#pragma once

#include <ostream>

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
	unsigned char** createAdjustedBoard(const unsigned char pawn_colour) const;
	void handleQuestion(char* question) const;
	bool isBoardCorrect() const;
	bool isGameOver(const unsigned char pawn_colour) const;
	unsigned char isGameOver() const;
	bool isLossPossible(const unsigned char pawn_colour) const;
	bool isBoardPossible() const;
	bool canWinWithNaiveOpponent(const unsigned char pawn_colour, const unsigned char moves) const;
	bool canWinWithPerfectOpponent(const unsigned char pawn_colour, const unsigned char moves) const;
	void debugPrint(unsigned char** board) const;
	void debugPrint() const;
};

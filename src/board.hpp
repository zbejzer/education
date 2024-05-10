#pragma once

#include <ostream>

#include "stack.hpp"

#define PAWN_EMPTY 0
#define PAWN_RED 1
#define PAWN_BLUE 2
const unsigned char PAWNS_ORDER[] = { PAWN_RED, PAWN_BLUE };

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
	unsigned char** createAdjustedBoard(const unsigned char pawn_colour) const;
	unsigned char isRedTurnNow() const;
	void generateBestPossibleTurns(const unsigned char pawn_colour, Stack<Board>& possible_turns) const;
	void generateAllPossibleTurns(const unsigned char pawn_colour, const bool should_win, Stack<Board>& possible_turns) const;
public:
	unsigned char** board;
	unsigned char size;
	unsigned char red, blue;

	Board();
	Board(const Board& other);
	~Board();
	void setSize(const unsigned char size);
	unsigned char getPawnsCount() const;
	unsigned char getPawnsCount(const unsigned char pawn_colour) const;
	void addPawn(const unsigned char pawn_colour, const unsigned char col, const unsigned char row);
	void handleQuestion(char* question) const;
	bool isBoardCorrect() const;
	bool isGameOver(const unsigned char pawn_colour) const;
	unsigned char isGameOver() const;
	bool isLossInPreviousTurnPossible(const unsigned char pawn_colour) const;
	bool isBoardPossible() const;
	bool canWinWithNaiveOpponent(const unsigned char pawn_colour, const unsigned char moves) const;
	bool canWinWithPerfectOpponent(const unsigned char pawn_colour, const unsigned char moves) const;
	void debugPrint() const;

	Board& operator=(Board other);
};

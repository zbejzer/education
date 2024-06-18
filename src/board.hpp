#pragma once

#include <ostream>

#include "array_1D.hpp"
#include "array_2D.hpp"
#include "pawns.hpp"
#include "stack.hpp"

class Board
{
	static Array2D<PawnColour> board_red;
	static Array2D<PawnColour> board_blue;
	Array2D<PawnColour> *current_board;
	static Array2D<bool> visited_fields;

	bool posInRange(short col, short row) const;
	unsigned char isRedTurnNow() const;
	bool addPawnAndCheckForWin(const PawnColour target_pawn_colour, const unsigned char moves, const unsigned char start_col, const unsigned char start_row);
	void generateBestPossibleTurns(const PawnColour pawn_colour, Stack<Board>& possible_turns) const;
	void generateAllPossibleTurns(const PawnColour pawn_colour, const bool should_win, Stack<Board>& possible_turns) const;
	bool gameOverDfs(PawnColour target, const unsigned char col, const unsigned char row) const;
	bool isGameOverFast(const PawnColour target_pawn_colour);
	bool isGameOver(const PawnColour pawn_colour);
public:
	static constexpr int MAX_BOARD_SIZE = 11;
	unsigned char size;
	unsigned char red, blue;

	Board();
	Board(const Board& other);
	~Board();
	void setSize(const unsigned char size);
	unsigned char getPawnsCount() const;
	unsigned char getPawnsCount(const PawnColour pawn_colour) const;
	void addPawn(const PawnColour pawn_colour, const unsigned char col, const unsigned char row);
	void updateBlueBoard();
	//void handleQuestion(char* question) const;
	bool isBoardCorrect() const;
	PawnColour isGameOver();
	bool isLossInPreviousTurnPossible(const PawnColour pawn_colour);
	bool isBoardPossible();
	bool canWinWithNaiveOpponent(const PawnColour pawn_colour, const unsigned char moves);
	bool canWinWithPerfectOpponent(const PawnColour pawn_colour, const unsigned char moves) const;
	void debugPrint() const;

	Board& operator=(Board other);
};

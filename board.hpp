#pragma once

#define PAWN_EMPTY 0
#define PAWN_RED 1
#define PAWN_BLUE 2

class Board
{
public:
	unsigned char** board;
	unsigned char size;
	unsigned char red, blue;

	Board();
	~Board();
	void setSize(const unsigned char& size);
	void createBoard();
	void destroyBoard();
	void handleQuestion(char* question);
	bool isBoardCorrect();
	void debugPrint();
};

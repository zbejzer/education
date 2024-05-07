#include "board.hpp"

Board::Board()
	: board(nullptr)
	, size(0)
{
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

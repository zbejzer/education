#include <cstdio>

#include "board.hpp"

using namespace	std;

int main()
{
    char buf = 0;

	while (buf != EOF)
	{
		unsigned char size = 0;
		Board board;
		while (buf != '\n')
		{
			buf = static_cast<char>(getchar());
			size++;
		}
		
		board.setSize((size - 2) / 3);
		board.createBoard();
		board.destroyBoard();
	}

    return 0;
}
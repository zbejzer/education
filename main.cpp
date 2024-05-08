#include <cstring>
#include <iostream>

#include "board.hpp"

using namespace	std;

// Transforming this input
//           ---
//        --<   >--
//     --< b >-<   >--
//  --< r >-<   >-<   >--
// < b >-< b >-<   >-< r >
//  --<   >-< r >-< b >--
//     --<   >-< r >--
//        --<   >--
//           ---
//
// into
// 
// /-------\
// | | | |r|
// |-+-+-+-|
// |b| | |b|
// |-+-+-+-|
// |r|b|r|r|
// |-+-+-+-|
// |b| | | |
// \-------/

int main()
{
	char buff[96] = "";
	cin.getline(buff, 96);

	while (cin.good() && !cin.eof())
	{
		Board board;
		board.size = static_cast<unsigned char>((strlen(buff) - 1) / 3);
		board.createBoard();
		buff[0] = '\0';

		for (unsigned char line = 0; line < board.size * 2; line++)
		{
			unsigned char offset = 0;
			while (buff[0] != '\n')
			{
				cin.get(buff[0]);

				if (buff[0] == '<') {
					unsigned char row, col;
					static_cast<void>(cin.get());
					cin.get(buff[0]);

					if (line < board.size)
					{
						row = line - offset;
						col = offset;
					}
					else
					{
						row = board.size - offset - 1;
						col = line - board.size + offset + 1;
					}

					if (buff[0] == 'r') {
						board.board[col][row] = PAWN_RED;
						board.red++;
					}
					else if (buff[0] == 'b')
					{
						board.board[col][row] = PAWN_BLUE;
						board.blue++;
					}
					else
					{
						board.board[col][row] = PAWN_EMPTY;
					}
					offset++;
				}
			}
			buff[0] = '\0';
		}

		// board.debugPrint();

		buff[0] = '\0';
		while (buff[0] != ' ' && cin.good() && !cin.eof())
		{
			cin.getline(buff, 96);
			board.handleQuestion(buff);
		}
	}

	return 0;
}
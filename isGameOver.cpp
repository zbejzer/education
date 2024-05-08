#include "board.hpp"
#include "stack.hpp"

unsigned char Board::isGameOver() const
{
	static const char d_row[6] = { -1,  0, 1, -1, 1, 0 };
	static const char d_col[6] = { -1, -1, 0,  0, 1, 1 };
	static const unsigned char target_pawn[2] = { PAWN_RED, PAWN_BLUE };

	for (unsigned char pawn_i = 0; pawn_i < 2; pawn_i++)
	{
		bool exists_1 = false, exists_2 = false;
		unsigned char** test_board = createAdjustedBoard(target_pawn[pawn_i]);
		Pos cur_pos;

		// debugPrint(test_board);

		for (unsigned char i = 0; i < size; i++)
		{
			if (test_board[0][i] == target_pawn[pawn_i])
			{
				exists_1 = true;
				break;
			}
		}
		for (unsigned char i = 0; i < size; i++)
		{
			if (test_board[size - 1][i] == target_pawn[pawn_i])
			{
				exists_2 = true;
				break;
			}
		}

		if (!(exists_1 && exists_2))
		{
			continue;
		}

		bool** visited = new bool* [size];
		for (unsigned char i = 0; i < size; i++)
		{
			visited[i] = new bool[size];
			for (unsigned char j = 0; j < size; j++)
			{
				visited[i][j] = false;
			}
		}

		Stack<Pos> to_visit;
		short test_col = 0, test_row = 0;

		for (unsigned char row = 0; row < size; row++)
		{
			if (test_board[0][row] == target_pawn[pawn_i])
			{
				to_visit.push(Pos(0, row));
			}
		}

		while (!to_visit.empty() && cur_pos.col != size - 1)
		{
			// to_visit.print();
			cur_pos = to_visit.top();
			visited[cur_pos.col][cur_pos.row] = true;
			to_visit.pop();

			for (unsigned char i = 0; i < 6; i++)
			{
				test_col = cur_pos.col + d_col[i];
				test_row = cur_pos.row + d_row[i];

				if (posInRange(test_col, test_row) && test_board[test_col][test_row] == target_pawn[pawn_i] && !visited[test_col][test_row])
				{
					to_visit.push(Pos(static_cast<unsigned char>(test_col), static_cast<unsigned char>(test_row)));
				}
			}
		}

		for (unsigned char i = 0; i < size; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;

		destroyBoard(test_board);

		if (cur_pos.col == size - 1)
		{
			return target_pawn[pawn_i];
		}
	}

	return PAWN_EMPTY;
}

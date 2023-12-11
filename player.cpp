#include "player.h"

using namespace std;

Player createPlayer(const PlayerColor color)
{
	Player new_player;

	new_player.color = color;
	
	if (color == PlayerColor::red)
	{
		new_player.pieces[BOARD_SIZE - 0 - 1] = 2;
		new_player.pieces[BOARD_SIZE - 11 - 1] = 5;
		new_player.pieces[BOARD_SIZE - 16 - 1] = 3;
		new_player.pieces[BOARD_SIZE - 18 - 1] = 5;
	}
	else {
		new_player.pieces[0] = 2;
		new_player.pieces[11] = 5;
		new_player.pieces[16] = 3;
		new_player.pieces[18] = 5;
	}

	return Player();
}

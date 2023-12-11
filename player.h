#pragma once

#include <cstdint>

#include "constants.h"

enum PlayerColor
{
	white,
	red
};

struct Player
{
	uint8_t pieces[BOARD_SIZE];
	PlayerColor color;
};

Player createPlayer(const PlayerColor);
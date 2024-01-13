#include "game.h"
#include "common.h"

uint8_t Game::isStarted()
{
    return started;
}

void Game::start()
{
    player.show();
    started = 1;
}

void Game::stop()
{
    player.hide();
    started = 0;
}

Game::Game() 
	: quit{0}
	, current_level{0}
	, started{0}
{
}
#include "Game.h"

Game* Game::instance = nullptr;

Game::Game()
	: quit{0}
{
}

Game* Game::getInstance()
{
	return Game::instance;
}

void Game::setInstance(Game* new_instance)
{
	Game::instance = new_instance;
}

void Game::nextTurn()
{
}

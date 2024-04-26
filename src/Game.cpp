#include "Game.h"

#include <SDL.h>

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

void Game::destroyInstance(Game* instance)
{
	if (instance != nullptr)
	{
		delete instance;
	}
	else {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Attempted to destroy null game instance");
	}
}

void Game::destroyInstance()
{
	destroyInstance(Game::instance);
}

void Game::nextTurn()
{
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Next turn.\n");
}

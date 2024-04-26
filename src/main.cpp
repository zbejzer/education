#include <iostream>
#include <SDL.h>

#include "App.h"
#include "Game.h"

int main(int argc, char* args[])
{
	App::setInstance(new App());
	App& app = *App::getInstance();
	Game::setInstance(new Game());
	Game& game = *Game::getInstance();

	app.initSDL();

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "App started");
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting Game");
	while (!game.quit)
	{
		app.calculateDeltaTime();
		app.prepareScene();
		app.doInput();
		app.presentScene();
	};

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Stopping game");
	Game::destroyInstance();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Stopping app");
	app.deinitSDL();
	App::destroyInstance();

	return 0;
}
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

	while (!game.quit)
	{
		app.calculateDeltaTime();
		app.prepareScene();
		app.doInput();
		app.presentScene();

		SDL_Delay(4);
	};

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Stopping app");
	app.deinitSDL();

	return 0;
}
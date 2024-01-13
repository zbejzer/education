#include <math.h>
#include <stdio.h>
#include <string.h>

#include"SDL.h"
#include"SDL_main.h"

#include "app.h"
#include "game.h"
#include "player.h"
#include "draw.h"
#include "defs.h"

App app;
Game game;
Player player;

int main(int argc, char** argv)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "App started");

	int min_frametime = 1000 / MAX_FPS;

	app.initSDL();
    initPlayer();

	while (!game.quit)
    {
        app.calculateDeltaTime();
		app.prepareScene();
        app.doInput();
        app.doEvents();
        player.handleInput();
        player.handleMovement();
        player.calculateMovement();
        player.render();
        app.presentScene();

        app.frames++;

		SDL_Delay(min_frametime);
	};

	app.deinitSDL();

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "App stopped properly");

	return 0;
};

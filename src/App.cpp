#include "App.h"
#include "Game.h"

App* App::instance = nullptr;

App::App()
	: last_time{ 0 }
	, delta{ 0 }
	, window{ nullptr }
	, renderer{ nullptr }
	, event{ NULL }
{
}

App* App::getInstance()
{
	return App::instance;
}

void App::setInstance(App* new_instance)
{
	instance = new_instance;
}

void App::destroyInstance(App* instance)
{
	if (instance != nullptr)
	{
		delete instance;
	}
	else {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Attempted to destroy null app instance");
	}
}

void App::destroyInstance()
{
	destroyInstance(App::instance);
}

void App::initSDL()
{
	int renderer_flags = SDL_RENDERER_ACCELERATED;
	int windowFlags = 0;
	char window_name[] = "Wirtualny Swiat - Stanislaw Borodziuk 2024";

	SDL_LogSetAllPriority(LOG_LEVEL);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "SDL_Init error: %s", SDL_GetError());
		exit(1);
	}

#ifdef ENABLE_FULLSCREEN_MODE
	windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
	instance->window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, windowFlags)
#else
	instance->window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, windowFlags);
#endif

	if (instance->window == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to create window: %s", SDL_GetError());
		exit(1);
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	instance->renderer = SDL_CreateRenderer(instance->window, -1, renderer_flags);

	if (instance->renderer == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		exit(1);
	};

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_ShowCursor(SDL_ENABLE);
}

void App::deinitSDL()
{
	// freeing all textures
	for (SDL_Texture* i : textures)
	{
		SDL_DestroyTexture(i);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void App::calculateDeltaTime()
{
	int new_time = SDL_GetTicks();
	delta = (new_time - last_time) * 0.001;
	last_time = new_time;
}

void App::doInput()
{
	Game& game = *Game::getInstance();
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			// SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Key pressed: %s", SDL_GetKeyName(event.key.keysym.sym));
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				game.quit = 1;
				[[fallthrough]];
			case SDLK_RETURN:
				game.nextTurn();
				[[fallthrough]];
			default:
				break;
			}
			break;
		}
		case SDL_QUIT:
			game.quit = 1;
			break;
		};
	};
}

void App::prepareScene()
{
	SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
	SDL_RenderClear(renderer);
}

void App::presentScene()
{
	SDL_RenderPresent(renderer);
}

void App::registerTexture(SDL_Texture* texture)
{
	textures.push_back(texture);
}
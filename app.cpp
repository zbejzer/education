#include "app.h"

#include "SDL.h"
#include "SDL_main.h"

#include "common.h"
#include "defs.h"

void App::calculateFPS()
{
    fps = frames / FAST_TIMER_INTERVAL;
    frames = 0;
}

void App::doSlowEvents()
{
}

void App::doFastEvents()
{
    // fps
    calculateFPS();

    SDL_LogVerbose(SDL_LOG_CATEGORY_VIDEO, "FPS: %d", (int)fps);
}

void App::doKeyAction(SDL_KeyboardEvent *event, uint8_t is_down)
{
    if (!event->repeat)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "New key (%d) state (%d) detected", event->keysym.sym, is_down);
        switch (event->keysym.sym)
        {
        case SDLK_ESCAPE:
            if (is_down)
            {
                game.quit = 1;
            }
            break;
        case SDLK_w:
            controls.up = is_down;
            break;
        case SDLK_a:
            controls.left = is_down;
            break;
        case SDLK_s:
            controls.down = is_down;
            break;
        case SDLK_d:
            controls.right = is_down;
            break;
        case SDLK_SPACE:
            controls.space = is_down;
            break;
        default:
            break;
        }
    }
}

void App::initSDL()
{
    int renderer_flags = SDL_RENDERER_ACCELERATED;
    int windowFlags = 0;
    char window_name[] = "Donkey King - Stanislaw Borodziuk 2024";

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Falied to initilize SDL: %s", SDL_GetError());
        exit(1);
    }

#ifdef ENABLE_FULLSCREEN_MODE
    windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
    app.window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, windowFlags)
#else
    app.window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, windowFlags);
#endif

        if (app.window == NULL)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        exit(1);
    };

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flags);

    if (app.renderer == NULL)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        exit(1);
    };

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_ShowCursor(SDL_DISABLE);

#if defined(ENABLE_DEBUG_LOG)
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#elif defined(ENABLE_VERBOSE_LOG)
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
#endif

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL initialized successfully");
}

void App::deinitSDL()
{
    // freeing all surfaces
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::calculateDeltaTime()
{
    int new_time = SDL_GetTicks();
    delta = (new_time - last_time) * 0.001;
    last_time = new_time;
    world_time += delta;
    slow_timer += delta;
    fast_timer += delta;
}

void App::doEvents()
{
    if (fast_timer > FAST_TIMER_INTERVAL)
    {
        doFastEvents();
        fast_timer -= FAST_TIMER_INTERVAL;
    }

    if (slow_timer > SLOW_TIMER_INTERVAL)
    {
        doSlowEvents();
        slow_timer -= SLOW_TIMER_INTERVAL;
    }
}

void App::doInput()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            doKeyAction(&event.key, 1);
            break;
        case SDL_KEYUP:
            doKeyAction(&event.key, 0);
            break;
        case SDL_QUIT:  
            game.quit = 1;
            break;
        default:
            break;
        }
    };
}

void App::prepareScene()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void App::presentScene()
{
    SDL_RenderPresent(renderer);
}

App::App()
    : slow_timer{0}
    , fast_timer{0}
    , last_time{0}
    , frames{0}
    , delta{0}
    , world_time{0}
    , fps{0}
    , ui_border_top{0}
    , ui_border_bottom{0}
    , controls{Controls()}
{
}

#pragma once

#include <SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// #define ENABLE_FULLSCREEN_MODE
#define ENABLE_FPS_LOG
#define LOG_LEVEL SDL_LOG_PRIORITY_VERBOSE

class App
{
    static App* instance;

    int last_time;
    double delta;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

public:
    App();

    static App* getInstance();
    static void setInstance(App* new_instance);
    static void destroyInstance(App* instance);
    static void destroyInstance();
    static const double inputTimeout;

    void initSDL();
    void deinitSDL();
    void calculateDeltaTime();
    void doInput();
    void prepareScene();
    void presentScene();
};
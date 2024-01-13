#pragma once

#include"SDL.h"
#include"SDL_main.h"

#include "controls.h"

class App
{
    int last_time, ui_border_top, ui_border_bottom;
    double slow_timer, fast_timer;

    SDL_Window *window;
    SDL_Event event;

    void calculateFPS();
    void doSlowEvents();
    void doFastEvents();
    void doKeyAction(SDL_KeyboardEvent *event, uint8_t is_down);

  public:
    int frames;
    double delta, world_time, fps;
    Controls controls;
    SDL_Renderer *renderer;

    void initSDL();
    void deinitSDL();
    void calculateDeltaTime();
    void doEvents();
    void doInput();
    void prepareScene();
    void presentScene();

    App();
};
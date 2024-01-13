#pragma once
#include <cstdint>

#include "entity.h"

class Game
{
    uint8_t started;
  public:
    int quit;
    unsigned int current_level;
    uint8_t isStarted();
    void start();
    void stop();

    Game();
};
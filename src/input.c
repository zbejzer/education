#include "jfrog/input.h"

#include <stdio.h>

#include "jfrog/app.h"

namespace input {
  void pollInput(Input & _input, WINDOW * window) {
    _input.skipped_ticks++;

    if (_input.skipped_ticks < app::TICKRATE / INPUT_TICKRATE) {
      return;
    }

    _input.skipped_ticks = 0;

    tryRelease(_input);

    int ch;
    while ((ch = wgetch(window)) != ERR) {
      switch (ch) {
        case KEY_F(1):
          registerKeyDown(_input.keys[_input.kF1]);
          break;
        case KEY_F(2):
          registerKeyDown(_input.keys[_input.kF2]);
          break;
        case 'w':
        case 'W':
          registerKeyDown(_input.keys[_input.kUp]);
          break;
        case 'a':
        case 'A':
          registerKeyDown(_input.keys[_input.kLeft]);
          break;
        case 's':
        case 'S':
          registerKeyDown(_input.keys[_input.kDown]);
          break;
        case 'd':
        case 'D':
          registerKeyDown(_input.keys[_input.kRight]);
          break;
      }
    }

    verifyDownState(_input);
    // printDebugInfo(_input);
  }

  void registerKeyDown(Key & _key) {
    if (!_key.is_down) {
      _key.is_pressed = true;
    }
    _key.is_down = true;
    _key.is_released = false;
  }

  void setInputDownState(Input & _input, bool state) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      _input.keys[i].is_down = state;
    }
  }

  void setInputReleasedState(Input & _input, bool state) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      _input.keys[i].is_released = state;
    }
  }

  void setInputPressedState(Input & _input, bool state) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      _input.keys[i].is_pressed = state;
    }
  }

  // Set is_released flags to see which keys are still down
  void tryRelease(Input & _input) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      if (_input.keys[i].is_down) {
        _input.keys[i].is_released = true;
      }
    }
  }

  // Clear is_down flags for keys which have is_released state
  void verifyDownState(Input & _input) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      if (_input.keys[i].is_released) {
        _input.keys[i].is_down = false;
      }
    }
  }

  void printDebugInfo(Input & _input) {
    for (size_t i = 0; i < sizeof(_input.keys) / sizeof(_input.keys[0]); i++) {
      if (_input.keys[i].is_down) {
        std::cerr << "Key " << i << " down" << std::endl;
      }
      if (_input.keys[i].is_pressed) {
        std::cerr << "Key " << i << " pressed" << std::endl;
      }
      if (_input.keys[i].is_released) {
        std::cerr << "Key " << i << " released" << std::endl;
      }
    }
    std::cerr << std::endl;
  }

}  // namespace input
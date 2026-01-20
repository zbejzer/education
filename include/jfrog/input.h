#ifndef JFROG_INPUT_H
#define JFROG_INPUT_H

#include <stdbool.h>

const unsigned int INPUT_TICKRATE = 16;  // frequency of ticks per second

typedef struct Key {
  bool is_down;
  bool is_released;
  bool is_pressed;
} Key;

typedef struct Input {
  enum KeyCodes { kUp = 0, kDown = 1, kRight = 2, kLeft = 3, kF1 = 4, kF2 = 5 };

  unsigned int skipped_ticks;
  Key keys[6];
} Input;

void inputPoll(Input* _input, WINDOW* window);
void inputRegisterKeyDown(Key* _key);
void inputSetDownState(Input* _input, bool state);
void inputSetReleasedState(Input* _input, bool state);
void inputSetPressedState(Input* _input, bool state);
void inputTryRelease(Input* _input);
void inputVerifyDownState(Input* _input);
void inputPrintDebugInfo(Input* _input);

#endif
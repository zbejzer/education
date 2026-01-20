#ifndef JFROG_INPUT_H
#define JFROG_INPUT_H

namespace input {

constexpr unsigned int INPUT_TICKRATE = 16;  // frequency of ticks per second

struct Key {
  bool is_down;
  bool is_released;
  bool is_pressed;
};

struct Input {
  enum KeyCodes { kUp = 0, kDown = 1, kRight = 2, kLeft = 3, kF1 = 4, kF2 = 5 };

  unsigned int skipped_ticks;
  Key keys[6];
};

void pollInput(Input& _input, WINDOW* window);
void registerKeyDown(Key& _key);
void setInputDownState(Input& _input, bool state);
void setInputReleasedState(Input& _input, bool state);
void setInputPressedState(Input& _input, bool state);
void tryRelease(Input& _input);
void verifyDownState(Input& _input);
void printDebugInfo(Input& _input);

}  // namespace input

#endif
#include "jfrog/input.h"

#include <stdbool.h>
#include <stdio.h>

#include "jfrog/app.h"

void inputPoll(Input *_input)
{
    // _input->skipped_ticks++;

    // if (_input->skipped_ticks < TICKRATE / INPUT_TICKRATE) {
    //   return;
    // }

    // _input->skipped_ticks = 0;

    // inputTryRelease(_input);

    // int ch;
    // while ((ch = wgetch(window)) != ERR) {
    //   switch (ch) {
    //     case KEY_F(1):
    //       inputRegisterKeyDown(_input->keys[_input->kF1]);
    //       break;
    //     case KEY_F(2):
    //       inputRegisterKeyDown(_input->keys[_input->kF2]);
    //       break;
    //     case 'w':
    //     case 'W':
    //       inputRegisterKeyDown(_input->keys[_input->kUp]);
    //       break;
    //     case 'a':
    //     case 'A':
    //       inputRegisterKeyDown(_input->keys[_input->kLeft]);
    //       break;
    //     case 's':
    //     case 'S':
    //       inputRegisterKeyDown(_input->keys[_input->kDown]);
    //       break;
    //     case 'd':
    //     case 'D':
    //       inputRegisterKeyDown(_input->keys[_input->kRight]);
    //       break;
    //   }
    // }

    // inputVerifyDownState(_input);
    // // inputPrintDebugInfo(_input);
}

void inputRegisterKeyDown(Key *_key)
{
    if (!_key->is_down)
    {
        _key->is_pressed = true;
    }
    _key->is_down = true;
    _key->is_released = false;
}

void inputSetDownState(Input *_input, bool state)
{
    for (size_t i = 0; i < sizeof(_input->keys) / sizeof(_input->keys[0]); i++)
    {
        _input->keys[i].is_down = state;
    }
}

void inputSetReleasedState(Input *_input, bool state)
{
    for (size_t i = 0; i < sizeof(_input->keys) / sizeof(_input->keys[0]); i++)
    {
        _input->keys[i].is_released = state;
    }
}

void inputSetPressedState(Input *_input, bool state)
{
    for (size_t i = 0; i < sizeof(_input->keys) / sizeof(_input->keys[0]); i++)
    {
        _input->keys[i].is_pressed = state;
    }
}

// Set is_released flags to see which keys are still down
void inputTryRelease(Input *_input)
{
    for (size_t i = 0; i < sizeof(_input->keys) / sizeof(_input->keys[0]); i++)
    {
        if (_input->keys[i].is_down)
        {
            _input->keys[i].is_released = true;
        }
    }
}

// Clear is_down flags for keys which have is_released state
void inputVerifyDownState(Input *_input)
{
    for (size_t i = 0; i < sizeof(_input->keys) / sizeof(_input->keys[0]); i++)
    {
        if (_input->keys[i].is_released)
        {
            _input->keys[i].is_down = false;
        }
    }
}

const unsigned int INPUT_TICKRATE = 16;
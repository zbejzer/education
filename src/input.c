#include "jfrog/input.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#endif

#include "jfrog/app.h"

void inputInit(Input *_input)
{
    inputSetState(_input, 0);

    return;
}

void inputDeinit(Input *_input)
{
    return;
}

void inputPoll(Input *_input)
{
    unsigned char pressed_key_index = UCHAR_MAX;

#ifdef _WIN32
    pressed_key_index = inputGetPressedKeyWindows();
#else
    exit(1); // not implemented for other platforms
#endif

    inputSetState(_input, 0);
    if (pressed_key_index != UCHAR_MAX)
    {
        _input->keys[pressed_key_index] = true;
    }

    return;
}

void inputSetState(Input *_input, unsigned char state)
{
    memset(_input->keys, state, sizeof _input->keys);
}

unsigned char inputGetPressedKeyWindows()
{
    if (_kbhit())
    {
        char ch = _getch();

        if (ch == 'w' || ch == 'W')
        {
            return (unsigned char)JFROG_KEY_UP;
        }
        if (ch == 's' || ch == 'S')
        {
            return (unsigned char)JFROG_KEY_DOWN;
        }
        if (ch == 'a' || ch == 'A')
        {
            return (unsigned char)JFROG_KEY_LEFT;
        }
        if (ch == 'd' || ch == 'D')
        {
            return (unsigned char)JFROG_KEY_RIGHT;
        }
        if (ch == 'q' || ch == 'Q')
        {
            return (unsigned char)JFROG_KEY_QUIT;
        }
    }

    return UCHAR_MAX;
}
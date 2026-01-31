#ifndef JFROG_INPUT_H
#define JFROG_INPUT_H

#include <stdbool.h>
#include <stdint.h>

#define JFROG_KEY_UP 0
#define JFROG_KEY_DOWN 1
#define JFROG_KEY_RIGHT 2
#define JFROG_KEY_LEFT 3
#define JFROG_KEY_QUIT 4

typedef struct Input
{
    bool keys[5];
} Input;

void inputInit(Input *_input);
void inputDeinit(Input *_input);
void inputPoll(Input *_input);
void inputSetState(Input *_input, unsigned char state);
unsigned char inputGetPressedKeyWindows();

#endif
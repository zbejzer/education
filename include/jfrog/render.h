#ifndef JFROG_RENDER_H
#define JFROG_RENDER_H

#include <stddef.h>

typedef struct Screen {
  size_t height;
  size_t width;
  char* buffer;
} Screen;

void renderHideCursor(void);
void renderShowCursor(void);

void renderInit(Screen* _screen);
void renderDeinit(Screen* _screen);
void renderClearBuffer(Screen* const _screen);
void renderDrawBuffer(Screen* const _screen);

extern Screen* k_screen;

#endif
#include "jfrog/render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jfrog/config.h"

void renderHideCursor(void) { printf("\033[?25l"); }

void renderShowCursor(void) { printf("\033[?25h"); }

void renderInit(Screen* _screen) {
  _screen->height = k_config->window_game_height + k_config->window_ui_height;
  _screen->width = k_config->window_width;
  _screen->buffer =
      (char*)malloc(sizeof(char) * _screen->height * _screen->width);
}

void renderDeinit(Screen* _screen) {
  free(_screen->buffer);
  _screen->buffer = NULL;
}

void renderClearBuffer(Screen* const _screen) {
  memset(_screen->buffer, ' ',
         (size_t)_screen->height * (size_t)_screen->width);
}

void renderDrawBuffer(Screen* const _screen) {
  // move cursor to home
  printf("\033[H");

  for (size_t y = 0; y < _screen->height; y++) {
    for (size_t x = 0; x < _screen->width; x++) {
      putchar(_screen->buffer[y * _screen->width + x]);
    }
    putchar('\n');
  }
}

Screen* k_screen = NULL;

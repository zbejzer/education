#ifndef JFROG_RENDER_H
#define JFROG_RENDER_H

#include <stddef.h>

typedef struct Screen
{
    size_t height_game;
    size_t height_ui;
    size_t width;
    size_t border_size;
    size_t game_buffer_size;
    size_t ui_buffer_size;

    char *game_buffer;
    char *ui_buffer;
} Screen;

void renderHideCursor(void);
void renderShowCursor(void);
void renderClearConsole(void);

void renderInit(Screen *_screen);
void renderDeinit(Screen *_screen);
void renderCreateUi(Screen *_screen);
void renderCreateBorders(Screen *const _screen);
void renderPutTextUi(Screen *const _screen, const char *_str, size_t _x, size_t _y);
void renderPutTextGame(Screen *const _screen, const char *_str, size_t _x, size_t _y);
void renderClearBuffer(Screen *const _screen);
void renderDrawBuffer(Screen *const _screen);

#endif
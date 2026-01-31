#include "jfrog/render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jfrog/config.h"
#include "jfrog/game.h"

void renderHideCursor(void)
{
    printf("\033[?25l");
}

void renderShowCursor(void)
{
    printf("\033[?25h");
}

void renderClearConsole(void)
{
    // move cursor to home
    printf("\033[H");
    // clear console
    printf("\033[J");

    fflush(stdout);
}

void renderInit(Screen *_screen)
{
    // include 1 char-wide borders
    _screen->height_game = (size_t)k_config->window_game_height;
    _screen->height_ui = (size_t)k_config->window_ui_height;
    _screen->width = (size_t)k_config->window_width;
    _screen->border_size = (size_t)k_config->border_size;

    _screen->game_buffer_size = _screen->height_game * _screen->width;
    _screen->ui_buffer_size = _screen->height_ui * _screen->width;

    _screen->game_buffer = (char *)malloc(sizeof(char) * _screen->game_buffer_size);
    _screen->ui_buffer = (char *)malloc(sizeof(char) * _screen->ui_buffer_size);
}

void renderDeinit(Screen *_screen)
{
    free(_screen->game_buffer);
    _screen->game_buffer = NULL;
    free(_screen->ui_buffer);
    _screen->ui_buffer = NULL;
}

void renderCreateUi(Screen *_screen)
{
    char time_left_buff[32] = "";
    char score_buff[32] = "";

    sprintf(time_left_buff, "Czas do konca: %d", (int)k_game->time_left);
    sprintf(score_buff, "Wynik: %d", (int)k_game->score);

    renderPutTextUi(_screen, "Sterowanie", 1, 0);
    renderPutTextUi(_screen, "W S A D - Sterowanie postacia", 1, 1);
    renderPutTextUi(_screen, "Q - Wyjscie", 1, 2);
    renderPutTextUi(_screen, time_left_buff, 41, 1);
    renderPutTextUi(_screen, score_buff, 41, 2);
    renderCreateBorders(_screen);
}

void renderCreateBorders(Screen *const _screen)
{
    // game part of the screen
    for (size_t y = 0; y < _screen->height_game; y++)
    {
        for (size_t x = 0; x < _screen->width; x++)
        {
            if (x == 0 || x == _screen->width - _screen->border_size || y == 0 ||
                y == _screen->height_game - _screen->border_size)
            {
                _screen->game_buffer[y * _screen->width + x] = '*';
            }
        }
    }

    // ui part of the screen
    for (size_t y = 0; y < _screen->height_ui; y++)
    {
        for (size_t x = 0; x < _screen->width; x++)
        {
            if (x == 0 || x == _screen->width - _screen->border_size || y == 0 ||
                y == _screen->height_ui - _screen->border_size)
            {
                _screen->ui_buffer[y * _screen->width + x] = '*';
            }
        }
    }
}

void renderPutTextUi(Screen *const _screen, const char *_str, size_t _x, size_t _y)
{
    size_t offset = (_y + _screen->border_size) * _screen->width + _x + _screen->border_size;
    strncpy(_screen->ui_buffer + offset, _str, strlen(_str));
}

void renderPutTextGame(Screen *const _screen, const char *_str, size_t _x, size_t _y)
{
    size_t offset = (_y + _screen->border_size) * _screen->width + _x + _screen->border_size;
    strncpy(_screen->game_buffer + offset, _str, strlen(_str));
}

void renderPutCharGame(Screen *const _screen, const char _ch, size_t _x, size_t _y)
{
    size_t offset = (_y + _screen->border_size) * _screen->width + _x + _screen->border_size;
    _screen->game_buffer[offset] = _ch;
}

void renderClearBuffer(Screen *const _screen)
{
    memset(_screen->game_buffer, ' ', _screen->game_buffer_size);
    memset(_screen->ui_buffer, ' ', _screen->ui_buffer_size);
}

void renderDrawBuffer(Screen *const _screen)
{
    // move cursor to home
    printf("\033[H");

    // print game part of the screen
    for (size_t y = 0; y < _screen->height_game; y++)
    {
        for (size_t x = 0; x < _screen->width; x++)
        {
            putchar(_screen->game_buffer[y * _screen->width + x]);
        }
        putchar('\n');
    }

    // print ui part of the screen
    for (size_t y = 0; y < _screen->height_ui; y++)
    {
        for (size_t x = 0; x < _screen->width; x++)
        {
            putchar(_screen->ui_buffer[y * _screen->width + x]);
        }
        putchar('\n');
    }

    fflush(stdout);
}
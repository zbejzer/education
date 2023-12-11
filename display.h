#pragma once

#include "player.h"
#include <ncurses/curses.h>

void initScreen(WINDOW **game_window, WINDOW **menu_window);
void drawBoard(WINDOW **game_window);
void printUpperField(WINDOW **game_window, const int start_y, const int start_x, const int field_num);
void printLowerField(WINDOW **game_window, const int start_y, const int start_x, const int field_num);
void drawPlayerPieces(WINDOW **game_window, const Player player);
void printPlayerPiece(WINDOW **game_window, const int start_y, const int start_x, const Player player,
                      const int field_num);
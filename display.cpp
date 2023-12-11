#include "display.h"

#include <cstdio>
#include <ncurses/curses.h>

#include "constants.h"

void initScreen(WINDOW **game_window, WINDOW **menu_window)
{
    int start_x, start_y;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_y = (LINES - WINDOW_GAME_HEIGHT) / 2;
    start_x = (COLS - WINDOW_GAME_WIDTH - WINDOW_MENU_WIDTH) / 2;

    *game_window = newwin(WINDOW_GAME_HEIGHT, WINDOW_GAME_WIDTH, start_y, start_x);
    *menu_window = newwin(WINDOW_MENU_HEIGHT, WINDOW_MENU_WIDTH, start_y, start_x + WINDOW_GAME_WIDTH);
    box(*game_window, 0, 0);
    box(*menu_window, 0, 0);
}

void drawBoard(WINDOW **game_window)
{
    constexpr int field_width = 7;
    constexpr int offset_y = 3, offset_x = 2;
    int board_field = 1;
    int x_pos = 0;

    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        printUpperField(game_window, offset_y, x_pos + offset_x, board_field);
        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }

    x_pos = 0;
    int y_start_pos = getmaxy(*game_window) - 1;
    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        printLowerField(game_window, y_start_pos - offset_y, x_pos + offset_x, board_field);
        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }
}

void printUpperField(WINDOW **game_window, const int start_y, const int start_x, const int field_num)
{
    constexpr int offset_num_y = -2, offset_num_x = 2;

    char num_string[3];
    sprintf(num_string, "%-2d", field_num);

    wmove(*game_window, start_y + offset_num_y, start_x + offset_num_x);
    wprintw(*game_window, num_string);
    mvwprintw(*game_window, start_y, start_x, "=====");
    mvwprintw(*game_window, start_y + 1, start_x, " === ");
    mvwprintw(*game_window, start_y + 2, start_x, "  =  ");
}

void printLowerField(WINDOW **game_window, const int start_y, const int start_x, const int field_num)
{
    constexpr int offset_num_y = -2, offset_num_x = 2;

    char num_string[3];
    sprintf(num_string, "%-2d", field_num);

    wmove(*game_window, start_y - offset_num_y, start_x + offset_num_x);
    wprintw(*game_window, num_string);

    mvwprintw(*game_window, start_y - 2, start_x, "  =  ");
    mvwprintw(*game_window, start_y - 1, start_x, " === ");
    mvwprintw(*game_window, start_y, start_x, "=====");
}

void drawPlayerPieces(WINDOW **game_window, const Player player)
{
    constexpr int field_width = 7;
    constexpr int offset_y = 7, offset_x = 2;
    int x_pos = 0;
    int board_field = 1;

    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        if (player.pieces[board_field - 1] > 0)
        {
            printPlayerPiece(game_window, offset_y, x_pos + offset_x, player, board_field - 1);
        }

        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }

    x_pos = 0;
    int y_start_pos = getmaxy(*game_window) - 1;
    for (size_t x = 0; x < BOARD_SIZE / 2; x++)
    {
        if (player.pieces[board_field - 1] > 0)
        {
            printPlayerPiece(game_window, y_start_pos - offset_y, x_pos + offset_x, player, board_field - 1);
        }

        board_field++;
        x_pos += field_width;

        if (x + 1 == BOARD_SIZE / 4)
        {
            x_pos += field_width;
        }
    }
}

void printPlayerPiece(WINDOW **game_window, const int start_y, const int start_x, const Player player,
                      const int field_num)
{
    constexpr int offset_string_x = 0;
    char player_string[5];

    if (player.color == PlayerColor::red)
    {
        sprintf(player_string, "C: %-2d", player.pieces[field_num]);
    }
    else if (player.color == PlayerColor::white)
    {
        sprintf(player_string, "B: %-2d", player.pieces[field_num]);
    }

    mvwprintw(*game_window, start_y, start_x + offset_string_x, player_string);
}
#include <clocale>

#include <ncurses/curses.h>

#include "display.h"
#include "game.h"

using namespace std;

int main()
{
    WINDOW *game_window, *menu_window;

    initScreen(&game_window, &menu_window);
    drawBoard(&game_window);

    // Game game;
    // initGame(&game);

    /*while (!game.isEnd)
    {

    }*/

    // drawBoard();

    // refreshes the screen
    wrefresh(game_window);
    wrefresh(menu_window);

    // pause the screen output
    getch();
    getch();

    // deallocates memory and ends ncurses
    endwin();
    return 0;
}
#include "hello.hpp"

#include <ncurses/ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    mvaddch(0, 0, '+');
    mvaddch(LINES - 1, 0, '-');
    say_hello();
    refresh();

    getch();

    endwin();
}
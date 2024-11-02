#include "hello.hpp"

#include <ncurses/ncurses.h>

void say_hello()
{
    mvaddstr(10, 30, "Hello from function");
}

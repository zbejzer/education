#include <stdio.h>
#include <ncurses.h>

void main(){
	initscr();
 	start_color();
 	init_pair(1,COLOR_RED,COLOR_GREEN);
 	attrset(COLOR_PAIR(1));
 	move(10,30);
 	printw("%s","Ala ma kota");
 	refresh();
 	getchar();
 	endwin();
return;
}
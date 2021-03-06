/*
	Copyright (c) 2014 Andreas Wenzel, Teradata Germany
	License: You are free to use, adopt and modify this program for your particular
	purpose.
	If you don't have any relationship with Teradata, you will find this tool
	probably not very useful.
	LICENSOR IS NOT LIABLE TO LICENSEE FOR ANY DAMAGES, INCLUDING COMPENSATORY,
	SPECIAL, INCIDENTAL, EXEMPLARY, PUNITIVE, OR CONSEQUENTIAL DAMAGES, CONNECTED
	WITH OR RESULTING FROM THIS LICENSE AGREEMENT OR LICENSEE'S USE OF THIS SOFTWARE.

	It is appreciated, if any changes to the source code are reported
	to the copyright holder.
*/

#include "Standards.h"
#include <stdlib.h> //noetig fuer atexit()
#include <ncurses.h>
#include <locale.h>
#include <getopt.h>
#include <ctype.h>
#include "CalcNumberColumns.h"
#include "MyCurses.h"
#include "quit.h"

void CursesInitialSetup(struct windim *work, WINDOW *headerwin, WINDOW *linenumwin, WINDOW *contentwin) {
	int screenx, screeny;
	unsigned int i;

	initscr();
	atexit(quit(headerwin, linenumwin, contentwin));

	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);

	bkgd(COLOR_PAIR(1));

	curs_set(0);

	getmaxyx(stdscr, screeny, screenx);

	work->x = screenx;
	work->y = screeny;

	headerwin = newwin(1, screenx - 5, 0, 5);
	wbkgd(headerwin, COLOR_PAIR(2));

	linenumwin = newwin(screeny - 1, 5, 1, 0);
	wbkgd(linenumwin, COLOR_PAIR(2));

	contentwin = newwin(screeny - 1, screenx - 5, 2, 6);
	wbkgd(contentwin, COLOR_PAIR(1));

	for (i = 0; i < screeny - 1; i++) {
		mvwprintw(linenumwin, i, 0, "%5u\n", i + 1);
	}

	mvwprintw(headerwin, 0, 0, "Test");

	scrollok(linenumwin, TRUE);
	scrollok(contentwin, TRUE);

	refresh();
	wrefresh(linenumwin);
	wrefresh(headerwin);
	wrefresh(contentwin);
}

/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "keyboard.h"

#ifdef _WIN32
#include <conio.h>

void keyboardInit() {}
void keyboardDestroy() {}

int keyhit() {
    return _kbhit();
}

int readch() {
    return _getch();
}

#else
#include <ncurses.h> //parte linux (Resolver...)

static int initialized = 0;

void keyboardInit() {
    if (initialized) return;
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    initialized = 1;
}

void keyboardDestroy() {
    if (!initialized) return;
    endwin();
    initialized = 0;
}

int keyhit() {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    }
    return 0;
}

int readch() {
    return getch();
}

#endif


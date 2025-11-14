#include "screen_size.h"

#ifdef _WIN32
#include <windows.h>

ScreenSize getScreenSize() {
    static int lastCols = 0;
    static int lastRows = 0;

    if (lastCols != 0 && lastRows != 0) {
        ScreenSize s = { lastCols, lastRows };
        return s;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    lastCols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    lastRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    ScreenSize s = { lastCols, lastRows };
    return s;
}

#else
#include <sys/ioctl.h> //parte linux (Resolver...)
#include <unistd.h>

ScreenSize getScreenSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    ScreenSize s = { w.ws_col, w.ws_row };
    return s;
}

#endif

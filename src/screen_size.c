#include "screen_size.h"

#ifdef _WIN32
#include <windows.h>

ScreenSize getScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return (ScreenSize){80, 24};

    int cols = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

    return (ScreenSize){cols, rows};
}

#else
#include <sys/ioctl.h>
#include <unistd.h>

ScreenSize getScreenSize()
{
    struct winsize w;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return (ScreenSize){80, 24};

    return (ScreenSize){w.ws_col, w.ws_row};
}

#endif

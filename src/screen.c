#include <stdio.h>
#include "screen.h"
#include "screen_size.h"

int MINX = 1;
int MINY = 1;
int MAXX = 80;
int MAXY = 24;

int SCRSTARTX = 3;
int SCRENDX   = 75;
int SCRSTARTY = 1;
int SCRENDY   = 23;

void screenInit(int drawBorders)
{
    //pega o tamanho do terminal
    ScreenSize s = getScreenSize();

    MAXX = s.cols;
    MAXY = s.rows;

    MINX = 1;
    MINY = 1;

    int offsetX = 0;
    int offsetY = 0;

#ifdef __MSYS__
    offsetX = 1;
    offsetY = 1;
#elif defined(__MINGW32__) || defined(__MINGW64__)
    offsetX = 1;
    offsetY = 1;
#else
    offsetX = 0;
    offsetY = 0;
#endif

    SCRSTARTX = 1 + offsetX;
    SCRSTARTY = 1 + offsetY;

    SCRENDX = MAXX - offsetX;
    SCRENDY = MAXY - offsetY;

    SCRSTARTX += 1;
    SCRSTARTY += 1;

    SCRENDX -= 1;
    SCRENDY -= 1;

    screenHideCursor();
    screenClear();

    if (drawBorders)
    {
        screenBoxEnable();

        screenGotoxy(SCRSTARTX, SCRSTARTY);
        putchar(BOX_UPLEFT);
        for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
            putchar(BOX_HLINE);
        putchar(BOX_UPRIGHT);

        for (int y = SCRSTARTY + 1; y < SCRENDY; y++)
        {
            screenGotoxy(SCRSTARTX, y);
            putchar(BOX_VLINE);

            screenGotoxy(SCRENDX, y);
            putchar(BOX_VLINE);
        }

        screenGotoxy(SCRSTARTX, SCRENDY);
        putchar(BOX_DWNLEFT);
        for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
            putchar(BOX_HLINE);
        putchar(BOX_DWNRIGHT);

        screenBoxDisable();
    }

    screenUpdate();
}

void screenGotoxy(int x, int y)
{
    printf("%s[%d;%dH", ESC, y, x);
}

void screenSetColor(screenColor fg, screenColor bg)
{
    printf("%s[%d;%dm", ESC, 30 + fg, 40 + bg);
}

void screenDestroy()
{
    screenSetNormal();
    screenShowCursor();
    screenClear();
}

void screenClearInside()
{
    for (int y = SCRSTARTY + 1; y < SCRENDY; y++)
    {
        for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
        {
            screenGotoxy(x, y);
            putchar(' ');
        }
    }
}


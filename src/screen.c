/**
 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <stdio.h>
#include "screen.h"
#include "screen_size.h"
// #include "screen_size.h" // REMOVIDO/COMENTADO: Dependência problemática

// Definicoes de variáveis globais (necessário, pois foram declaradas como 'extern' em screen.h)
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
    ScreenSize s = getScreenSize();

    MAXX = s.cols;
    MAXY = s.rows;

    MINX = 1;
    MINY = 1;

    SCRSTARTX = 2;
    SCRSTARTY = 2;

    SCRENDX = MAXX - 2;
    SCRENDY = MAXY - 2;

    if (SCRENDX < SCRSTARTX) SCRENDX = SCRSTARTX + 1;
    if (SCRENDY < SCRSTARTY) SCRENDY = SCRSTARTY + 1;

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

    fflush(stdout);
}

void screenGotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void screenFullClear()
{
    printf("\033[2J");   
    printf("\033[H");    
    fflush(stdout);
}


void screenSetColor(screenColor fg, screenColor bg)
{
    printf("\033[%d;%dm", 30 + fg, 40 + bg);
}

void screenDestroy()
{
    screenSetNormal();
    screenShowCursor();
    screenClear();
    fflush(stdout);
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
    fflush(stdout);
}

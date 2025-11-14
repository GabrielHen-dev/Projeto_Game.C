#include "player.h"
#include "screen.h"
#include <stdio.h>
#include <string.h>

void playerInit(Player* p, int startX, int startY, const char* simbolo)
{
    p->x = startX;
    p->y = startY;
    p->oldX = startX;
    p->oldY = startY;

    strcpy(p->simbolo, simbolo);
}

void playerErase(Player* p)
{
    screenGotoxy(p->oldX, p->oldY);
    printf("   ");
}

void playerDraw(Player* p)
{
    screenGotoxy(p->x, p->y);
    printf("%s", p->simbolo);
}

void playerMove(Player* p, int dx, int dy)
{
    p->oldX = p->x;
    p->oldY = p->y;

    p->x += dx;
    p->y += dy;
}

#include <stdio.h>
#include <string.h>
#include "player.h"
#include "screen.h"

char DEFAULT_PLAYER_NAME[32] = "Player";

void playerInit(Player* p, int startX, int startY, const char* simbolo)
{
    p->x = startX;
    p->y = startY;
    p->oldX = startX;
    p->oldY = startY;
    p->drawX = startX;
    p->drawY = startY;
    p->drawNameX = startX;
    if (startY - 1 > SCRSTARTY)
        p->drawNameY = startY - 1;
    else
        p->drawNameY = startY + 1;

    strcpy(p->simbolo, simbolo);
    strncpy(p->name, DEFAULT_PLAYER_NAME, sizeof(p->name)-1);
    p->name[sizeof(p->name)-1] = '\0';
}

void playerErase(Player* p)
{
    size_t len = strlen(p->simbolo);

    if (p->drawX > 0 && p->drawY > 0) {
        screenGotoxy(p->drawX, p->drawY);
        for (size_t i = 0; i < len; ++i) putchar(' ');
    }
    if ((p->oldX != p->drawX || p->oldY != p->drawY) && p->oldX > 0 && p->oldY > 0) {
        screenGotoxy(p->oldX, p->oldY);
        for (size_t i = 0; i < len; ++i) putchar(' ');
    }
    if (p->drawNameY > SCRSTARTY && p->drawNameY < SCRENDY) {
        screenGotoxy(p->drawNameX, p->drawNameY);
        size_t nlen = strlen(p->name);
        for (size_t i = 0; i < nlen; ++i) putchar(' ');
    }
}

void playerDraw(Player* p)
{
    screenGotoxy(p->x, p->y);
    printf("%s", p->simbolo);

    if (p->name[0] != '\0') {
        size_t nlen = strlen(p->name);
        int nameX = p->x - (int)(nlen / 2);
        if (nameX < SCRSTARTX + 1) nameX = SCRSTARTX + 1;
        if (nameX + (int)nlen > SCRENDX - 1) nameX = SCRENDX - 1 - (int)nlen;
        int nameY = p->y - 1;
        if (nameY <= SCRSTARTY) {
            nameY = p->y + 1; 
            if (nameY >= SCRENDY) nameY = p->y; 
        }
        if (nameY > SCRSTARTY && nameY < SCRENDY) {
            screenGotoxy(nameX, nameY);
            printf("%s", p->name);
            p->drawNameX = nameX;
            p->drawNameY = nameY;
        }
    }

    p->drawX = p->x;
    p->drawY = p->y;
}

void playerMove(Player* p, int dx, int dy)
{
    p->oldX = p->x;
    p->oldY = p->y;

    p->x += dx;
    p->y += dy;
}

void playerUpdateDraw(Player* p)
{
    screenGotoxy(p->drawX, p->drawY);
    size_t len = strlen(p->simbolo);
    for (size_t i = 0; i < len; ++i) putchar(' ');

    if (p->drawNameY > SCRSTARTY && p->drawNameY < SCRENDY) {
        screenGotoxy(p->drawNameX, p->drawNameY);
        size_t nlen = strlen(p->name);
        for (size_t i = 0; i < nlen; ++i) putchar(' ');
    }

    screenGotoxy(p->x, p->y);
    printf("%s", p->simbolo);

    if (p->name[0] != '\0') {
        size_t nlen = strlen(p->name);
        int nameX = p->x - (int)(nlen / 2);
        if (nameX < SCRSTARTX + 1) nameX = SCRSTARTX + 1;
        if (nameX + (int)nlen > SCRENDX - 1) nameX = SCRENDX - 1 - (int)nlen;
        int nameY = p->y - 1;
        if (nameY <= SCRSTARTY) {
            nameY = p->y + 1;
            if (nameY >= SCRENDY) nameY = p->y;
        }
        
        if (nameY > SCRSTARTY && nameY < SCRENDY) {
            screenGotoxy(nameX, nameY);
            printf("%s", p->name);
            p->drawNameX = nameX;
            p->drawNameY = nameY;
        }
    }

    p->drawX = p->x;
    p->drawY = p->y;
}

void playerSetName(Player* p, const char* name)
{
    if (!p || !name) return;
    strncpy(p->name, name, sizeof(p->name)-1);
    p->name[sizeof(p->name)-1] = '\0';
}

void playerSetDefaultName(const char* name)
{
    if (!name) return;
    strncpy(DEFAULT_PLAYER_NAME, name, sizeof(DEFAULT_PLAYER_NAME)-1);
    DEFAULT_PLAYER_NAME[sizeof(DEFAULT_PLAYER_NAME)-1] = '\0';
}

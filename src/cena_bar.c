#include "cena_bar.h"
#include "screen.h"
#include "keyboard.h"
#include "npc.h"
#include "player.h"
#include "dialogo_dealer.h"
#include "musica.h"

#include <stdio.h>
#include <string.h>


static NPC bartender; //personagens
static NPC prof1, prof2, prof3, prof4;


void desenharBar()
{
    
    const char* titulo = "BAR DO ZE";
    int larg = strlen(titulo);
    int tx = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larg / 2);
    int ty = SCRSTARTY + 2;

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(tx, ty);
    printf("%s", titulo);

    int balcY = ty + 4;
    screenSetColor(LIGHTGRAY, BLACK);

    for (int x = SCRSTARTX + 3; x < SCRENDX - 3; x++)
    {
        screenGotoxy(x, balcY);
        putchar('=');
    }

    int bx = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2);
    int by = balcY - 1;

    npcInit(&bartender, bx, by, 'A', "Araujo"); //dealer
    npcDraw(&bartender);

    //mesas
    int m1x = SCRSTARTX + 8;
    int m1y = balcY + 4;

    int m2x = SCRENDX - 12;
    int m2y = balcY + 4;

    int m3x = SCRSTARTX + 8;
    int m3y = SCRENDY - 7;

    int m4x = SCRENDX - 12; 
    int m4y = SCRENDY - 7;

    screenSetColor(LIGHTGRAY, BLACK);

    //mesa1
    screenGotoxy(m1x, m1y);     printf("[ ]");
    screenGotoxy(m1x, m1y + 1); printf(" | ");

    //mesa2
    screenGotoxy(m2x, m2y);     printf("[ ]");
    screenGotoxy(m2x, m2y + 1); printf(" | ");

    //mesa3
    screenGotoxy(m3x, m3y);     printf("[ ]");
    screenGotoxy(m3x, m3y + 1); printf(" | ");

    //mesa4
    screenGotoxy(m4x, m4y);     printf("[ ]");
    screenGotoxy(m4x, m4y + 1); printf(" | ");

    //professores
    npcInit(&prof1, m1x - 3, m1y, 'G', "Guilherme");
    npcInit(&prof2, m2x + 5, m2y, 'D', "Diego");
    npcInit(&prof3, m3x - 3, m3y, 'B', "Baudel");
    npcInit(&prof4, m4x + 5, m4y, 'L', "Lucas");

    npcDraw(&prof1);
    npcDraw(&prof2);
    npcDraw(&prof3);
    npcDraw(&prof4);
}


void cenaBar()
{
    screenInit(1);
    desenharBar();
    musicaInit();  

    Player p; //player

    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2; //inicio player
    int pY = SCRENDY - 2;

    playerInit(&p, pX, pY, ":)");
    playerDraw(&p);
    screenUpdate();

    while (1)
    {
        if (keyhit())
        {
            int c = readch();

            p.oldX = p.x;
            p.oldY = p.y;

            if (c == 'w' || c == 'W') playerMove(&p, 0, -1);
            if (c == 's' || c == 'S') playerMove(&p, 0, +1);
            if (c == 'a' || c == 'A') playerMove(&p, -1, 0);
            if (c == 'd' || c == 'D') playerMove(&p, 1, 0);

            if (p.x <= SCRSTARTX + 1) p.x = SCRSTARTX + 1;
            if (p.x >= SCRENDX - 2)   p.x = SCRENDX - 2;
            if (p.y <= SCRSTARTY + 1) p.y = SCRSTARTY + 1;
            if (p.y >= SCRENDY - 1)   p.y = SCRENDY - 1;

            playerErase(&p);
            playerDraw(&p);

            musicaTick(); //anima musica

            screenUpdate();

            int ty = SCRSTARTY + 2;  //balcão
            int balcY = ty + 4;     
            int colY = balcY + 1;   

            if (p.y == colY &&
                p.x >= SCRSTARTX + 3 &&
                p.x <= SCRENDX - 3)
            {
                dialogoDealer();

                screenInit(1);
                desenharBar();
                musicaInit();
                playerDraw(&p);
                screenUpdate();
            }

            if (p.y == SCRENDY - 1)
                return;
        }
    }
}

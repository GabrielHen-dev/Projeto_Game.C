#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cena_jogo.h"
#include "screen.h"
#include "keyboard.h"
#include "minigame_roleta.h"
#include "npc.h"
#include "player.h"
#include "musica.h"

void desenharMesa(int larguraMesa, int alturaMesa);
void desenharBar(void);

void cenaJogo(NPC* professorEscolhido) {

    screenInit(1);
    screenClearInside();
    desenharBar();
    musicaInit();
   
    int larguraMesa = 5;
    int alturaMesa = 5;

    int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larguraMesa / 2);
    int inicioY = SCRSTARTY + 14; 

    npcErase(professorEscolhido);
    professorEscolhido->x = inicioX + larguraMesa + 3;
    professorEscolhido->y = inicioY + 2;
    npcDraw(professorEscolhido);

    Player p;
    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    int pY = SCRSTARTY + 8;

    playerInit(&p, pX, pY, ":)");
    playerDraw(&p);
    screenUpdate();

    while (1) {
        if (keyhit())
        {
            int c = readch();

            
            if (c == 'q' || c == 'Q' || c == 27) {
                return; 
            }

            int dx = 0, dy = 0;

            if (c == 'w' || c == 'W') dy = -1;
            if (c == 's' || c == 'S') dy = +1;
            if (c == 'a' || c == 'A') dx = -1;
            if (c == 'd' || c == 'D') dx = +1;

            if (dx != 0 || dy != 0) {
                
                playerMove(&p, dx, dy);

                if (p.x <= SCRSTARTX + 1) p.x = SCRSTARTX + 1;
                if (p.x >= SCRENDX - 2)   p.x = SCRENDX - 2;
                if (p.y <= SCRSTARTY + 1) p.y = SCRSTARTY + 1;
                if (p.y >= SCRENDY - 1)   p.y = SCRENDY - 1;

                
                playerErase(&p);

                
                playerDraw(&p);
            }

            screenUpdate();

            if (p.x == inicioX - 2 &&
                p.y >= inicioY &&
                p.y <= inicioY + alturaMesa - 1)
            {
                minigameRoleta(professorEscolhido);
                return; 
            }


            if (p.y == SCRENDY - 1)
                return;
        }
    }
}

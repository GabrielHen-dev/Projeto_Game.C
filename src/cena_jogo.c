#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "cena_jogo.h"
#include "minigame_roleta.h"
#include "npc.h"
#include "player.h"
#include "musica.h"
#include "collision.h"


extern NPC bartender;
extern NPC prof1, prof2, prof3, prof4;
extern int exitDoorX ;
extern int exitDoorY ;
extern int exitDoorW ;

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
    professorEscolhido->y = inicioY + 3;
    npcDraw(professorEscolhido);

    Player p;
    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    int pY = SCRSTARTY + 7;

    playerInit(&p, pX, pY + 2 , ":)");
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

            /*Colisão com borda, se ele ultrapassar*/
            if (p.x < SCRSTARTX + 1 || p.x > SCRENDX - 2 || p.y < SCRSTARTY + 1 || p.y > SCRENDY - 1)
            {
                p.x = p.oldX;
                p.y = p.oldY;
            }
            /*colisão, considera nome e símbolo (player)*/
            AABB pa_sym = { p.x, p.y, (int)strlen(p.simbolo), 1 };

            int nameW = (int)strlen(p.name);
            int nameX = p.x - nameW / 2;
            int nameY = p.y - 1;
            AABB pa_name = { nameX, nameY, nameW > 0 ? nameW : 0, 1 };

            int collided = 0;

            AABB ba = { bartender.x, bartender.y, 1, 1 };
            if (aabb_overlap(&pa_sym, &ba) || (pa_name.w>0 && aabb_overlap(&pa_name, &ba))) collided = 1;

            if (!collided && bartender.nome != NULL) {
                AABB bname = { bartender.x - 1, bartender.y - 1, (int)strlen(bartender.nome), 1 };
                if (aabb_overlap(&pa_sym, &bname) || (pa_name.w>0 && aabb_overlap(&pa_name, &bname))) collided = 1;
            }

            /* professores */
            AABB a;
            a.w = 1; a.h = 1;

            a.x = prof1.x; a.y = prof1.y;
            if (!collided && (aabb_overlap(&pa_sym, &a) || (pa_name.w>0 && aabb_overlap(&pa_name, &a)))) collided = 1;
            if (!collided && prof1.nome != NULL) { AABB n1 = { prof1.x - 1, prof1.y - 1, (int)strlen(prof1.nome), 1 }; if (aabb_overlap(&pa_sym, &n1) || (pa_name.w>0 && aabb_overlap(&pa_name, &n1))) collided = 1; }

            a.x = prof2.x; a.y = prof2.y;
            if (!collided && (aabb_overlap(&pa_sym, &a) || (pa_name.w>0 && aabb_overlap(&pa_name, &a)))) collided = 1;
            if (!collided && prof2.nome != NULL) { AABB n2 = { prof2.x - 1, prof2.y - 1, (int)strlen(prof2.nome), 1 }; if (aabb_overlap(&pa_sym, &n2) || (pa_name.w>0 && aabb_overlap(&pa_name, &n2))) collided = 1; }

            a.x = prof3.x; a.y = prof3.y;
            if (!collided && (aabb_overlap(&pa_sym, &a) || (pa_name.w>0 && aabb_overlap(&pa_name, &a)))) collided = 1;
            if (!collided && prof3.nome != NULL) { AABB n3 = { prof3.x - 1, prof3.y - 1, (int)strlen(prof3.nome), 1 }; if (aabb_overlap(&pa_sym, &n3) || (pa_name.w>0 && aabb_overlap(&pa_name, &n3))) collided = 1; }

            a.x = prof4.x; a.y = prof4.y;
            if (!collided && (aabb_overlap(&pa_sym, &a) || (pa_name.w>0 && aabb_overlap(&pa_name, &a)))) collided = 1;
            if (!collided && prof4.nome != NULL) { AABB n4 = { prof4.x - 1, prof4.y - 1, (int)strlen(prof4.nome), 1 }; if (aabb_overlap(&pa_sym, &n4) || (pa_name.w>0 && aabb_overlap(&pa_name, &n4))) collided = 1; }

            /* mesa central desenharMesa(4,4) */
            if (!collided) {
                int larguraMesa = 5;
                int alturaMesa = 5;
                int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - ((larguraMesa) / 2);
                int inicioY = SCRSTARTY + 15;
                AABB mesaC = { inicioX, inicioY, larguraMesa, alturaMesa };
                if (aabb_overlap(&pa_sym, &mesaC) || (pa_name.w>0 && aabb_overlap(&pa_name, &mesaC))) collided = 1;
            }

            if (!collided) {
                int ty = SCRSTARTY + 2;
                int balcY = ty + 4;

                int m1x = SCRSTARTX + 8;
                int m1y = balcY + 4;

                int m2x = SCRENDX - 12;
                int m2y = balcY + 4;

                int m3x = SCRSTARTX + 8;
                int m3y = SCRENDY - 7;

                int m4x = SCRENDX - 12; 
                int m4y = SCRENDY - 7;

                AABB m1 = { m1x, m1y, 3, 2 };
                AABB m2 = { m2x, m2y, 3, 2 };
                AABB m3 = { m3x, m3y, 3, 2 };
                AABB m4 = { m4x, m4y, 3, 2 };

                if (aabb_overlap(&pa_sym, &m1) || aabb_overlap(&pa_sym, &m2) || aabb_overlap(&pa_sym, &m3) || aabb_overlap(&pa_sym, &m4) ||
                    (pa_name.w>0 && (aabb_overlap(&pa_name, &m1) || aabb_overlap(&pa_name, &m2) || aabb_overlap(&pa_name, &m3) || aabb_overlap(&pa_name, &m4))))
                {
                    collided = 1;
                }
            }

            if (!collided && pa_name.w>0 && pa_name.y < SCRSTARTY + 1) collided = 1;

            if (collided) { p.x = p.oldX; p.y = p.oldY; }

        
            playerUpdateDraw(&p);

            musicaTick(); 

            screenUpdate();

            if (exitDoorW > 0 && p.y == exitDoorY && p.x >= exitDoorX && p.x < exitDoorX + exitDoorW)
            {
                return; 
            }

            if (dx != 0 || dy != 0) {
                
                playerMove(&p, dx, dy);

                if (p.x <= SCRSTARTX + 1) p.x = SCRSTARTX + 1;
                if (p.x >= SCRENDX - 2)   p.x = SCRENDX - 2;
                if (p.y <= SCRSTARTY + 1) p.y = SCRSTARTY + 1;
                if (p.y >= SCRENDY - 1)   p.y = SCRENDY - 1;
                
                playerErase(&p);

                /* redraw the whole scene to restore any elements erased by playerErase */
                screenFullClear();
                screenInit(1);
                desenharBar();
                musicaInit();

                /* reposition and redraw the chosen professor for the jogo scene */
                professorEscolhido->x = inicioX + larguraMesa + 3;
                professorEscolhido->y = inicioY + 3;
                npcDraw(professorEscolhido);

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

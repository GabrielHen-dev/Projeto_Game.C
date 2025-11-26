#include "cena_bar.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "npc.h"
#include "player.h"
#include "dialogo_dealer.h"
#include "cena_selecao.h"
#include "cena_jogo.h"
#include "musica.h"
#include "collision.h"
#include "avatar_loader.h"
#include "screen.h"
#include "keyboard.h"



NPC bartender; 
NPC prof1, prof2, prof3, prof4;
int exitDoorX = 0;
int exitDoorY = 0;
int exitDoorW = 0;

static int any_overlap_recursive(const AABB* target, const AABB* list, int idx, int n)
{
    if (idx >= n) return 0;
    if (aabb_overlap(target, &list[idx])) return 1;
    return any_overlap_recursive(target, list, idx + 1, n);
}

 void desenharMesa(int larguraMesa, int alturaMesa) {
    int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larguraMesa / 2);
    int inicioY = SCRSTARTY + 15;

    screenGotoxy(inicioX, inicioY);
    printf("+");
    for (int i = 0; i < larguraMesa - 2; i++) printf("-");
    printf("+");

    for (int j = 1; j < alturaMesa - 1; j++) {
        screenGotoxy(inicioX, inicioY + j);
        printf("|");
        for (int i = 0; i < larguraMesa - 2; i++) printf(" ");
        printf("|");
    }

    screenGotoxy(inicioX, inicioY + alturaMesa - 1);
    printf("+");
    for (int i = 0; i < larguraMesa - 2; i++) printf("-");
    printf("+");
}



void desenharBar() {
    
    const char* titulo = "BAR DO ARAUJO";
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

    desenharMesa(5,5);

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

    //tenta rodar os desenhos dos personagens, caso não, roda só os traço*/
    int nlines = 0;
    char** tmp = NULL;

    tmp = load_avatar_from_file("assets/guilherme.txt", &nlines);
    if (tmp) {
        npcSetAvatar(&prof1, (const char**)tmp, nlines);
        for (int i = 0; i < nlines; ++i) free(tmp[i]);
        free(tmp);
    }

    tmp = load_avatar_from_file("assets/diego.txt", &nlines);
    if (tmp) {
        npcSetAvatar(&prof2, (const char**)tmp, nlines);
        for (int i = 0; i < nlines; ++i) free(tmp[i]);
        free(tmp);
    }

    tmp = load_avatar_from_file("assets/baudel.txt", &nlines);
    if (tmp) {
        npcSetAvatar(&prof3, (const char**)tmp, nlines);
        for (int i = 0; i < nlines; ++i) free(tmp[i]);
        free(tmp);
    }

    tmp = load_avatar_from_file("assets/lucas.txt", &nlines);
    if (tmp) {
        npcSetAvatar(&prof4, (const char**)tmp, nlines);
        for (int i = 0; i < nlines; ++i) free(tmp[i]);
        free(tmp);
    }

    npcDraw(&prof1);
    npcDraw(&prof2);
    npcDraw(&prof3);
    npcDraw(&prof4);

    const char* porta_saida = "[ SAIR ]";
    int pdw = strlen(porta_saida);
    int pdx = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (pdw / 2);
    int pdy = SCRENDY - 1;
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(pdx, pdy);
    printf("%s", porta_saida);
    screenSetColor(LIGHTGRAY, BLACK);

    exitDoorX = pdx; exitDoorY = pdy; exitDoorW = pdw;
}


void cenaBar() {
    screenInit(1);
    desenharBar();
    musicaInit();  

    Player p; //player

    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2; 
    int pY = SCRENDY - 2;

    playerInit(&p, pX, pY, ":)");
    playerUpdateDraw(&p);
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

            AABB* profBodies = calloc(4, sizeof(AABB));
            AABB* profNames = calloc(4, sizeof(AABB));
            if (profBodies != NULL && profNames != NULL) {
                profBodies[0].x = prof1.x; profBodies[0].y = prof1.y; profBodies[0].w = 1; profBodies[0].h = 1;
                profBodies[1].x = prof2.x; profBodies[1].y = prof2.y; profBodies[1].w = 1; profBodies[1].h = 1;
                profBodies[2].x = prof3.x; profBodies[2].y = prof3.y; profBodies[2].w = 1; profBodies[2].h = 1;
                profBodies[3].x = prof4.x; profBodies[3].y = prof4.y; profBodies[3].w = 1; profBodies[3].h = 1;

                profNames[0].x = prof1.x - 1; profNames[0].y = prof1.y - 1; profNames[0].w = prof1.nome ? (int)strlen(prof1.nome) : 0; profNames[0].h = 1;
                profNames[1].x = prof2.x - 1; profNames[1].y = prof2.y - 1; profNames[1].w = prof2.nome ? (int)strlen(prof2.nome) : 0; profNames[1].h = 1;
                profNames[2].x = prof3.x - 1; profNames[2].y = prof3.y - 1; profNames[2].w = prof3.nome ? (int)strlen(prof3.nome) : 0; profNames[2].h = 1;
                profNames[3].x = prof4.x - 1; profNames[3].y = prof4.y - 1; profNames[3].w = prof4.nome ? (int)strlen(prof4.nome) : 0; profNames[3].h = 1;

                if (!collided) {
                    if (any_overlap_recursive(&pa_sym, profBodies, 0, 4)) collided = 1;
                }
                if (!collided && pa_name.w > 0) {
                    if (any_overlap_recursive(&pa_name, profBodies, 0, 4)) collided = 1;
                    if (!collided && any_overlap_recursive(&pa_name, profNames, 0, 4)) collided = 1;
                }
            }
            free(profBodies);
            free(profNames);

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

                AABB* mesas = calloc(4, sizeof(AABB));
                if (mesas) {
                    mesas[0].x = m1x; mesas[0].y = m1y; mesas[0].w = 3; mesas[0].h = 2;
                    mesas[1].x = m2x; mesas[1].y = m2y; mesas[1].w = 3; mesas[1].h = 2;
                    mesas[2].x = m3x; mesas[2].y = m3y; mesas[2].w = 3; mesas[2].h = 2;
                    mesas[3].x = m4x; mesas[3].y = m4y; mesas[3].w = 3; mesas[3].h = 2;

                    if (any_overlap_recursive(&pa_sym, mesas, 0, 4)) collided = 1;
                    if (!collided && pa_name.w > 0 && any_overlap_recursive(&pa_name, mesas, 0, 4)) collided = 1;
                }
                free(mesas);
            }

            if (!collided && pa_name.w>0 && pa_name.y < SCRSTARTY + 1) collided = 1;

            if (collided) { p.x = p.oldX; p.y = p.oldY; }

            playerUpdateDraw(&p);

            /* restore mesas and professor names that playerUpdateDraw may have erased */
            {
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

                screenGotoxy(m1x, m1y);     printf("[ ]");
                screenGotoxy(m1x, m1y + 1); printf(" | ");
                screenGotoxy(m2x, m2y);     printf("[ ]");
                screenGotoxy(m2x, m2y + 1); printf(" | ");
                screenGotoxy(m3x, m3y);     printf("[ ]");
                screenGotoxy(m3x, m3y + 1); printf(" | ");
                screenGotoxy(m4x, m4y);     printf("[ ]");
                screenGotoxy(m4x, m4y + 1); printf(" | ");

                npcDraw(&prof1);
                npcDraw(&prof2);
                npcDraw(&prof3);
                npcDraw(&prof4);
                npcDraw(&bartender);
            }

            musicaTick(); 

            screenUpdate();

            if (exitDoorW > 0 && p.y == exitDoorY && p.x >= exitDoorX && p.x < exitDoorX + exitDoorW)
            {
                return; 
            }

            int ty = SCRSTARTY + 2;  
            int balcY = ty + 4;     
            int colY = balcY + 1;
            int colY2 = balcY + 2;    

            if ((p.y == colY ||p.y == colY2)&&
                p.x >= SCRSTARTX + 3 &&
                p.x <= SCRENDX - 3)
            {
                playerErase(&p);
                screenUpdate();
                char ret = dialogoDealer();
                if (ret >= 'A' && ret <= 'D')
                {
                    int escolha = (int)(ret - 'A');
                    NPC* inimigo = NULL;
                    switch (escolha)
                    {
                        case 0: inimigo = &prof1; break;
                        case 1: inimigo = &prof2; break;
                        case 2: inimigo = &prof3; break;
                        case 3: inimigo = &prof4; break;
                    }

                    if (inimigo != NULL)
                    {
                        cenaJogo(inimigo);
                    }
                }

                screenFullClear();
                screenInit(1);
                desenharBar();
                musicaInit();
                p.drawX = p.x; p.drawY = p.y;
                playerUpdateDraw(&p);
                screenUpdate();
            }
        }
    }
}

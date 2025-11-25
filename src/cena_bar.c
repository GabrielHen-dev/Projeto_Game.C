#include "cena_bar.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"

#include "npc.h"
#include "player.h"
#include "dialogo_dealer.h"
#include "cena_selecao.h"
#include "cena_jogo.h"
#include "musica.h"
#include "collision.h"
#include "avatar_loader.h"


static NPC bartender; //personagens
static NPC prof1, prof2, prof3, prof4;
static int exitDoorX = 0;
static int exitDoorY = 0;
static int exitDoorW = 0;
 /*interação removida, colisão...*/


 void desenharMesa(int larguraMesa, int alturaMesa)
{
    int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larguraMesa / 2);
    int inicioY = SCRSTARTY + 14;

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

    /*tenta rodar os desenhos dos personagens, caso não, roda só os traço*/
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


void cenaBar()
{
    screenInit(1);
    desenharBar();
    musicaInit();  

    Player p; //player

    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2; //inicio player
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
                int larguraMesa = 4;
                int alturaMesa = 4;
                int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larguraMesa / 2);
                int inicioY = SCRSTARTY + 14;
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

            musicaTick(); //anima musica

            screenUpdate();

            if (exitDoorW > 0 && p.y == exitDoorY && p.x >= exitDoorX && p.x < exitDoorX + exitDoorW)
            {
                return; 
            }

            int ty = SCRSTARTY + 2;  //balcão
            int balcY = ty + 4;     
            int colY = balcY + 1;   

            if (p.y == colY &&
                p.x >= SCRSTARTX + 3 &&
                p.x <= SCRENDX - 3)
            {
                playerErase(&p);
                screenUpdate();
                char ret = dialogoDealer();
                if (ret >= 'A' && ret <= 'D')
                {
                    int escolha = (int)(ret - 'A');
                    /* Map escolha to professor NPCs: 0->prof1, 1->prof2, 2->prof3, 3->prof4 */
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

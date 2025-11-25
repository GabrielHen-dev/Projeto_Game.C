#include "cena_jogo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"

#include "minigame_roleta.h"
#include "npc.h"
#include "player.h"
#include "musica.h"

void desenharMesa(int larguraMesa, int alturaMesa);
void desenharBar(void);


void cenaJogo(NPC* professorEscolhido)
{

    screenInit(1);
    screenClearInside();
    desenharBar();
    musicaInit();
   
    int larguraMesa = 5;
    int alturaMesa = 5;

    int inicioX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (larguraMesa / 2);
    int inicioY = SCRSTARTY + 14; // MESMO valor da sua desenharMesa

    // mover o professor escolhido para a direita da mesa
    // (apaga onde ele estava, muda x/y e desenha de novo)
    npcErase(professorEscolhido);
    professorEscolhido->x = inicioX + larguraMesa + 3;
    professorEscolhido->y = inicioY + 2;
    npcDraw(professorEscolhido);

    Player p;
    int pX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    int pY = SCRSTARTY + 7;

    playerInit(&p, pX, pY, ":)");
    playerDraw(&p);
    screenUpdate();

    while (1)
    {
        if (keyhit())
        {
            int c = readch();

            // opção extra pra sair da cena_jogo (Q ou ESC)
            if (c == 'q' || c == 'Q' || c == 27) {
                return; // volta pra cena_bar
            }

            int dx = 0, dy = 0;

            if (c == 'w' || c == 'W') dy = -1;
            if (c == 's' || c == 'S') dy = +1;
            if (c == 'a' || c == 'A') dx = -1;
            if (c == 'd' || c == 'D') dx = +1;

            if (dx != 0 || dy != 0)
            {
                // 1) move primeiro (atualiza oldX/oldY)
                playerMove(&p, dx, dy);

                // 2) limites nas bordas
                if (p.x <= SCRSTARTX + 1) p.x = SCRSTARTX + 1;
                if (p.x >= SCRENDX - 2)   p.x = SCRENDX - 2;
                if (p.y <= SCRSTARTY + 1) p.y = SCRSTARTY + 1;
                if (p.y >= SCRENDY - 1)   p.y = SCRENDY - 1;

                // 3) apaga onde ELE ESTAVA (usa oldX/oldY)
                playerErase(&p);

                // 4) desenha na nova posição (x/y)
                playerDraw(&p);
            }


            screenUpdate();

            // COLISÃO COM O LADO ESQUERDO DA MESA CENTRAL
            // lado esquerdo é: x = inicioX - 1
            // na altura da mesa (inicioY até inicioY + alturaMesa - 1)
            if (p.x == inicioX - 1 &&
                p.y >= inicioY &&
                p.y <= inicioY + alturaMesa - 1)
            {
                minigameRoleta(professorEscolhido);
                return; // depois do minigame, volta pra cena_bar
            }

            // se quiser também sair pela parte de baixo:
            if (p.y == SCRENDY - 1)
                return;
        }
    }
}

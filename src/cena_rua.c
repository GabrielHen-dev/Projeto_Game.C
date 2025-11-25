#include "cena_rua.h"

#include <string.h>

#include "screen.h"
#include "screen_size.h"
#include "keyboard.h"
#include "player.h"


static void desenharRuaBase()
{
    screenSetColor(LIGHTGRAY, BLACK);

    int midY = SCRSTARTY + ((SCRENDY - SCRSTARTY) - 1);
    int topY = SCRSTARTY + 1;

    //calçadaup
    for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
    {
        screenGotoxy(x, topY);
        putchar('#');
    }

    //calçadabx
    for (int x = SCRSTARTX + 1; x < SCRENDX; x++)
    {
        screenGotoxy(x, midY);
        putchar('#');
    }

    //porta
    screenSetColor(YELLOW, BLACK);

    const char* porta = "[  BAR  ]";
    int pw = strlen(porta);

    int portaX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - pw / 2;
    int portaY = midY - 1;

    screenGotoxy(portaX, portaY);
    printf("%s", porta);

    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(portaX, portaY + 1);
    for (int i = 0; i < pw; i++) putchar('#');

    screenUpdate();
}


void cenaRua()
{
    screenFullClear();   // limpa a tela.
    screenInit(1);
    int playerStartX = SCRSTARTX + 1; //player
    int playerStartY = SCRSTARTY + 4;

    Player p;
    playerInit(&p, playerStartX, playerStartY, ":)"); 

    desenharRuaBase();
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

            if (p.x <= SCRSTARTX + 1) p.x = SCRSTARTX + 1;
            if (p.x >= SCRENDX - 2)   p.x = SCRENDX - 2;
            if (p.y <= SCRSTARTY + 1) p.y = SCRSTARTY + 1;
            if (p.y >= SCRENDY - 1)   p.y = SCRENDY - 1;

            int midY = SCRSTARTY + ((SCRENDY - SCRSTARTY) - 1);; 
            int topCalcadaY = SCRSTARTY + 1;

            if (p.y == topCalcadaY)
                p.y = p.oldY;

            if (p.y == midY)
                p.y = p.oldY;


            playerUpdateDraw(&p);
            screenUpdate();

            const char* porta = "[  BAR  ]";
            int portaLargura = strlen(porta);
            int portaX = SCRSTARTX + ((SCRENDX - SCRSTARTX) / 2) - (portaLargura / 2);
            int portaY = midY - 1;

            if (p.y == portaY &&
                p.x >= portaX &&
                p.x < portaX + portaLargura)
            {
                return; //entra no bar
            }
        }
    }
}

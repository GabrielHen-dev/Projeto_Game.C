#include "cena_intro.h"
#include "screen.h"
#include "screen_size.h"
#include "keyboard.h"
#include <stdio.h>
#include <string.h>

void cenaIntro()
{
    screenHideCursor();

    const char* titulo = "MindShot";
    const char* dica   = "Pressione ENTER para continuar";

    int largTitulo = strlen(titulo);
    int largDica   = strlen(dica);

    //centraliza no meio
    int centroX = SCRSTARTX + (SCRENDX - SCRSTARTX) / 2;
    int centroY = SCRSTARTY + (SCRENDY - SCRSTARTY) / 2;

    int tituloX = centroX - largTitulo / 2;
    int tituloY = centroY - 1;

    int dicaX   = centroX - largDica / 2;
    int dicaY   = centroY + 1;

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(tituloX, tituloY);
    printf("%s", titulo);

    screenSetColor(LIGHTGRAY, BLACK);
    screenGotoxy(dicaX, dicaY);
    printf("%s", dica);

    screenUpdate();

    while (1) {
        if (keyhit()) {
            int c = readch();
            if (c == 13) return;
        }
    }
}


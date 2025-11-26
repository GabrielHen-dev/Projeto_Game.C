#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "screen_size.h"
#include "keyboard.h"
#include "player.h"
#include "cena_intro.h"

extern Player player;

void cenaIntro() {
    screenHideCursor();

    const char* titulo = "MINDSHOT";
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

    char namebuf[32] = "";
    int pos = 0;
    int promptX = centroX - 10;
    int promptY = centroY + 4; 
    screenGotoxy(promptX, promptY);
    printf("Nome: ");
    screenUpdate();

    while (1) {
        if (keyhit()) {
            int c = readch();
            if (c == 13 || c == 10) {
                if (pos > 0) {
                    namebuf[pos] = '\0';
                    playerSetDefaultName(namebuf);
                }
                return;
            }
            else if (c == 127 || c == 8) { 
                if (pos > 0) {
                    pos--; namebuf[pos] = '\0';
                    screenGotoxy(promptX + 6 + pos, promptY);
                    putchar(' ');
                    screenGotoxy(promptX + 6 + pos, promptY);
                    screenUpdate();
                }
            }
            else if (c >= 32 && c < 127 && pos < (int)sizeof(namebuf)-1) {
                namebuf[pos++] = (char)c; namebuf[pos] = '\0';
                screenGotoxy(promptX + 6 + pos - 1, promptY);
                putchar(c);
                screenUpdate();
            }
        }
    }
}
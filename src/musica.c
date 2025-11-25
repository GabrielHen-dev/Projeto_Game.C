#include <stdio.h>
#include "musica.h"
#include "screen.h"

//faixas para simular musica
static const char* frames[] = {
    "||#    ##    #    ##    #   ||",
    "||###  ####  ##   ####  ##  ||",
    "||####   ##  ###   ##  ###  ||",
    "||##   #####  ##  #####  ## ||",
    "||#  #######  ###  ###### # ||",
    "||##   #####  ##  #####  ## ||",
    "||####   ##  ###   ##  ###  ||",
    "||###  ####  ##   ####  ##  ||"
};

static int numFrames = sizeof(frames) / sizeof(frames[0]);
static int frameAtual = 0;

void musicaInit()
{
    frameAtual = 0;
    int yBanner = SCRSTARTY + 1;
    int xBanner = SCRSTARTX + 3;

    screenSetColor(LIGHTRED, BLACK);
    screenGotoxy(xBanner, yBanner);
    printf("ROCK - ESTILO AC/DC");

    int yEq = SCRSTARTY + 3;
    int xEq = SCRSTARTX + 4;

    screenGotoxy(xEq, yEq);
    printf("%s", frames[frameAtual]);
}

void musicaTick()
{
    frameAtual = (frameAtual + 1) % numFrames;

    int yEq = SCRSTARTY + 3;
    int xEq = SCRSTARTX + 4;

    screenSetColor(LIGHTRED, BLACK);
    screenGotoxy(xEq, yEq);
    printf("%s", frames[frameAtual]);
}

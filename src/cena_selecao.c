#include "cena_selecao.h"

#include <stdio.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"

/*7 linhas ASCII (oponentes)*/
static const char* av_guilherme[] = {
    "   _____   ",
    "  /  _  \\  ",
    " |  ( )  | ",
    " |   -   | ",
    " |  /|\\  | ",
    "  \\_/ \\_/  ",
    "   /   \\   "
};

static const char* av_diego[] = {
    "   _____   ",
    "  /     \\  ",
    " |  O O  | ",
    " |   ^   | ",
    " |  ---  | ",
    "  |  |  |  ",
    "   \\_/ \\_/ "
};

static const char* av_baudel[] = {
    "   _____   ",
    "  /- - -\\  ",
    " |  .'.  | ",
    " |  \\_/  | ",
    " |  '-'  | ",
    "  |  |  |  ",
    "   /   \\   "
};

static const char* av_lucas[] = {
    "   _____   ",
    "  /  ^  \\  ",
    " |  o o  | ",
    " |  \\_/  | ",
    " |  ---  | ",
    "  /| | |\\  ",
    "   /   \\   "
};

/*nomes e ponteiros*/
static const char* names[] = { "Guilherme", "Diego", "Baudel", "Lucas" };
static const char** avatars[] = { av_guilherme, av_diego, av_baudel, av_lucas };
static const int avatar_lines = 7;
static const int adversary_count = 4;

static void draw_option(int idx, int x, int y, int boxW, int selected)
{
    const char* name = names[idx];
    const char** av = avatars[idx];

    if (selected) screenSetReverse(); else screenSetNormal();

    /* desenhar avatar */
    for (int i = 0; i < avatar_lines; ++i)
    {
        int len = (int)strlen(av[i]);
        int pad = (boxW - len) / 2; if (pad < 0) pad = 0;
        screenGotoxy(x + pad, y + i);
        printf("%s", av[i]);
    }

    /* desenhar nome centralizado embaixo do avatar */
    int namelen = (int)strlen(name) + 2; /* extra spaces */
    int npad = (boxW - namelen) / 2; if (npad < 0) npad = 0;
    screenGotoxy(x + npad, y + avatar_lines);
    printf(" %s ", name);

    screenSetNormal();
}

int cenaSelecao()
{
    screenFullClear();
    screenInit(1);
    screenHideCursor();

    int cols = SCRENDX - SCRSTARTX - 2;
    int rows = SCRENDY - SCRSTARTY - 2;
    (void)cols; (void)rows;

    int availableW = SCRENDX - SCRSTARTX - 2;
    int availableH = SCRENDY - SCRSTARTY - 2; 

    int avatarW = 0;
    for (int i = 0; i < adversary_count; ++i)
    {
        for (int r = 0; r < avatar_lines; ++r)
        {
            int l = (int)strlen(avatars[i][r]); if (l > avatarW) avatarW = l;
        }
        int nl = (int)strlen(names[i]) + 2; if (nl > avatarW) avatarW = nl;
    }

    int minGap = 4;
    int totalBoxesW = adversary_count * avatarW;
    int gap = 0;
    if (availableW > totalBoxesW)
        gap = (availableW - totalBoxesW) / (adversary_count + 1);
    if (gap < minGap) gap = minGap;

    int totalWidth = adversary_count * avatarW + (adversary_count - 1) * gap;
    int startX = SCRSTARTX + 1 + (availableW - totalWidth) / 2;
    int startY = SCRSTARTY + 1 + (availableH - (avatar_lines + 1)) / 2;

    int selected = 0;

    screenSetColor(YELLOW, BLACK);
    screenGotoxy(SCRSTARTX + (SCRENDX - SCRSTARTX)/2 - 8, SCRSTARTY + 1);
    printf("SELECIONE O ADVERSARIO");
    screenSetColor(LIGHTGRAY, BLACK);

    while (1)
    {
        for (int i = 0; i < adversary_count; ++i)
        {
            int x = startX + i * (avatarW + gap);
            draw_option(i, x, startY, avatarW, i == selected);
        }

        screenGotoxy(SCRSTARTX + 2, SCRENDY - 2);
        printf("Use A/D ou <- -> para navegar, ENTER para escolher, ESC para cancelar");

        screenUpdate();

        int c = -1;
        while (!keyhit()) { /* esperar */ }
        c = readch();

        if (c == 'a' || c == 'A' || c == 68) { /* esquerda */
            selected = (selected - 1 + adversary_count) % adversary_count;
        }
        else if (c == 'd' || c == 'D' || c == 67) { /* direita */
            selected = (selected + 1) % adversary_count;
        }
        else if (c == 10 || c == 13) { /* enter */
            return selected;
        }
        else if (c == 27) { /* ESC */
            return -1;
        }

        /* limpar tela */
        for (int i = 0; i < adversary_count; ++i)
        {
            int x = startX + i * (avatarW + gap);
            for (int ly = 0; ly < avatar_lines + 1; ++ly)
            {
                screenGotoxy(x, startY + ly);
                for (int k = 0; k < avatarW; ++k) putchar(' ');
            }
        }
    }

    return -1;
}

#include "npc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

void npcInit(NPC* n, int x, int y, char simbolo, const char* nome)
{
    n->x = x;
    n->y = y;
    n->simbolo = simbolo;
    n->nome = nome;
    n->avatar = NULL;
    n->avatar_lines = 0;
    n->avatar_w = 0;
}

void npcSetAvatar(NPC* n, const char** avatar, int lines)
{
    if (!n) return;
    if (n->avatar != NULL && n->avatar_lines > 0) {
        ;
    }

    char** copy = (char**)calloc((size_t)lines, sizeof(char*));
    if (!copy) return;
    int maxw = 0;
    for (int i = 0; i < lines; ++i) {
        const char* src = avatar[i];
        size_t L = strlen(src);
        copy[i] = (char*)malloc(L + 1);
        if (copy[i]) {
            memcpy(copy[i], src, L + 1);
            if ((int)L > maxw) maxw = (int)L;
        } else {
            for (int j = 0; j < i; ++j) free(copy[j]);
            free(copy);
            return;
        }
    }
    /*limpa avatar que ficou*/
    if (n->avatar != NULL) {
        for (int j = 0; j < n->avatar_lines; ++j) free(n->avatar[j]);
        free(n->avatar);
    }
    n->avatar = copy;
    n->avatar_lines = lines;
    n->avatar_w = maxw;
}

static void free_avatar_lines_recursive(char** arr, int idx, int total)
{
    if (!arr) return;
    if (idx >= total) return;
    free_avatar_lines_recursive(arr, idx + 1, total);
    free(arr[idx]);
}

void npcClearAvatar(NPC* n)
{
    if (!n || !n->avatar) return;
    free_avatar_lines_recursive(n->avatar, 0, n->avatar_lines);
    free(n->avatar);
    n->avatar = NULL;
    n->avatar_lines = 0;
    n->avatar_w = 0;
}

void npcDraw(const NPC* n)
{
    if (!n) return;

    if (n->avatar != NULL && n->avatar_lines > 0) {
        int topx = n->x - n->avatar_w / 2;
        int topy = n->y - n->avatar_lines / 2;
        for (int i = 0; i < n->avatar_lines; ++i) {
            screenGotoxy(topx, topy + i);
            printf("%s", n->avatar[i]);
        }
        if (n->nome != NULL) {
            int namelen = (int)strlen(n->nome);
            int nx = topx + (n->avatar_w - namelen) / 2;
            screenGotoxy(nx, topy - 1);
            printf("%s", n->nome);
        }
    } else {
        if (n->nome != NULL) {
            screenGotoxy(n->x - 1, n->y - 1);
            printf("%s", n->nome);
        }
        screenGotoxy(n->x, n->y);
        putchar(n->simbolo);
    }
}

/*verifica ponteiro nulo e limpa NPC*/
void npcErase(const NPC* n)
{
    if (!n) return;

    if (n->avatar != NULL && n->avatar_lines > 0) {
        int topx = n->x - n->avatar_w / 2;
        int topy = n->y - n->avatar_lines / 2;
        for (int i = 0; i < n->avatar_lines; ++i) {
            screenGotoxy(topx, topy + i);
            for (int k = 0; k < n->avatar_w; ++k) putchar(' ');
        }
        if (n->nome != NULL) {
            int namelen = (int)strlen(n->nome);
            int nx = topx + (n->avatar_w - namelen) / 2;
            screenGotoxy(nx, topy - 1);
            for (int k = 0; k < namelen; ++k) putchar(' ');
        }
    } else {
        if (n->nome != NULL) {
            screenGotoxy(n->x - 1, n->y - 1);
            printf("   ");
        }
        screenGotoxy(n->x, n->y);
        putchar(' ');
    }
}

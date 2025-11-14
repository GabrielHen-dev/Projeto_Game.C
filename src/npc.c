#include "npc.h"
#include "screen.h"
#include <stdio.h>

void npcInit(NPC* n, int x, int y, char simbolo, const char* nome)
{
    n->x = x;
    n->y = y;
    n->simbolo = simbolo;
    n->nome = nome;
}

void npcDraw(const NPC* n)
{
    //cria nome
    if (n->nome != NULL)
    {
        screenGotoxy(n->x - 1, n->y - 1);
        printf("%s", n->nome);
    }

    screenGotoxy(n->x, n->y);
    putchar(n->simbolo);
}

void npcErase(const NPC* n)
{
    //apaga nome
    if (n->nome != NULL)
    {
        screenGotoxy(n->x - 1, n->y - 1);
        printf("   ");  
    }
    
    screenGotoxy(n->x, n->y);
    putchar(' ');
}

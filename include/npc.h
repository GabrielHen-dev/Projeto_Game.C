#ifndef NPC_H
#define NPC_H

typedef struct {
    int x;
    int y;
    char simbolo;   
    const char* nome; 
} NPC;


void npcInit(NPC* n, int x, int y, char simbolo, const char* nome);
void npcDraw(const NPC* n);
void npcErase(const NPC* n);

#endif

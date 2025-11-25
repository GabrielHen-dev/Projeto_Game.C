#ifndef NPC_H
#define NPC_H

typedef struct NPC {
    int x;
    int y;
    char simbolo;
    const char* nome;
    char** avatar;
    int avatar_lines;
    int avatar_w;
} NPC;

void npcInit(NPC* n, int x, int y, char simbolo, const char* nome);
void npcDraw(const NPC* n);
void npcErase(const NPC* n);
void npcSetAvatar(NPC* n, const char** avatar, int lines);
void npcClearAvatar(NPC* n);

#endif 

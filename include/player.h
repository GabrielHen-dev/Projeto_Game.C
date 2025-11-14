#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x, y;
    int oldX, oldY;
    char simbolo[8];
} Player;

void playerInit(Player* p, int startX, int startY, const char* simbolo);
void playerDraw(Player* p);
void playerErase(Player* p);
void playerMove(Player* p, int dx, int dy);

#endif
#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x, y;
    int oldX, oldY;
    int drawX, drawY;
    int drawNameX, drawNameY; 
    char simbolo[8];
    char name[32];
} Player;

void playerInit(Player* p, int startX, int startY, const char* simbolo);
void playerDraw(Player* p);
void playerErase(Player* p);
void playerMove(Player* p, int dx, int dy);
void playerUpdateDraw(Player* p);
void playerSetName(Player* p, const char* name);
void playerSetDefaultName(const char* name);

extern char DEFAULT_PLAYER_NAME[32];

#endif
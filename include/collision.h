
#ifndef COLLISION_H
#define COLLISION_H

typedef struct {
    int x;
    int y;
    int w;
    int h;
} AABB;

int aabb_overlap(const AABB* a, const AABB* b);

#endif 
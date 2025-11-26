
#ifndef COLLISION_H
#define COLLISION_H

typedef struct {
    int x;
    int y;
    int w;
    int h;
} AABB;

int aabb_overlap(const AABB* a, const AABB* b);
int aabb_overlap_list(const AABB* target, const AABB* list, int n);

#endif 
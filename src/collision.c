#include "collision.h"

int aabb_overlap(const AABB* a, const AABB* b)
{
    if (!a || !b) return 0;
    if (a->x + a->w <= b->x) return 0;
    if (b->x + b->w <= a->x) return 0;
    if (a->y + a->h <= b->y) return 0;
    if (b->y + b->h <= a->y) return 0;
    return 1;
}

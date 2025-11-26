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

static int aabb_overlap_list_recursive(const AABB* target, const AABB* list, int idx, int n)
{
    if (!target || !list) return 0;
    if (idx >= n) return 0;
    if (aabb_overlap(target, &list[idx])) return 1;
    return aabb_overlap_list_recursive(target, list, idx + 1, n);
}

int aabb_overlap_list(const AABB* target, const AABB* list, int n)
{
    return aabb_overlap_list_recursive(target, list, 0, n);
}

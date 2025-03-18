#include "point.h"
#include <stdlib.h>
#include <stdio.h>


PointPtr create_point(int x, int y) {
    PointPtr p = (PointPtr)malloc(sizeof(Point));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    p->x = x;
    p->y = y;
    return p;
}

void destroy_point(PointPtr p) {
    if (p != NULL) {
        free(p);
    }
}

int compare_points(const void* a, const void* b) {
    PointPtr p1 = *(PointPtr*)a;
    PointPtr p2 = *(PointPtr*)b;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return p1->x - p2->x;
}

double slope_to(PointPtr p1, PointPtr p2) {
    if (p1->x == p2->x && p1->y == p2->y) {
        return -1.0 / 0.0;
    }
    if (p1->x == p2->x) {
        return 1.0 / 0.0;
    }
    if (p1->y == p2->y) {
        return 0.0; 
    }
    return (double)(p2->y - p1->y) / (p2->x - p1->x);
}

int get_x(PointPtr p) {
    return p->x;
}

int get_y(PointPtr p) {
    return p->y;
}
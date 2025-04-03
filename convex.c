#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convex.h"

Point p0;

int compare_points(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->y != p2->y) return (p1->y < p2->y) ? -1 : 1;
    return (p1->x < p2->x) ? -1 : 1;
}

double getAngle(Point p0, Point p) {
    return atan2(p.y - p0.y, p.x - p0.x);
}

int compare_by_polar_angle(const void* a, const void* b) {
    Point* pointA = (Point*)a;
    Point* pointB = (Point*)b;
    double angleA = getAngle(p0, *pointA);
    double angleB = getAngle(p0, *pointB);

    if (angleA < angleB) return -1;
    if (angleA > angleB) return 1;

    int distA = (pointA->x - p0.x) * (pointA->x - p0.x) + (pointA->y - p0.y) * (pointA->y - p0.y);
    int distB = (pointB->x - p0.x) * (pointB->x - p0.x) + (pointB->y - p0.y) * (pointB->y - p0.y);
    return distA - distB;
}

int ccw(Point a, Point b, Point c) {
    int area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (area2 > 0) - (area2 < 0);
}

int convexHull(Point points[], int n, Point result[]) {
    if (n < 3) return 0;

    qsort(points, n, sizeof(Point), compare_points);
    p0 = points[0];

    qsort(points + 1, n - 1, sizeof(Point), compare_by_polar_angle);

    Point stack[MAX_POINTS];
    int stackSize = 0;
    stack[stackSize++] = points[0];
    stack[stackSize++] = points[1];

    for (int i = 2; i < n; i++) {
        while (stackSize >= 2 && ccw(stack[stackSize - 2], stack[stackSize - 1], points[i]) <= 0) {
            stackSize--;
        }
        stack[stackSize++] = points[i];
    }

    for (int i = 0; i < stackSize; i++) result[i] = stack[i];
    return stackSize;
}
void visualizeHull(Point points[], int n, Point hull[], int hullSize) {
    char grid[GRID_SIZE][GRID_SIZE];

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    for (int i = 0; i < n; i++) {
        if (points[i].x < GRID_SIZE && points[i].y < GRID_SIZE)
            grid[points[i].y][points[i].x] = 'o';
    }

    for (int i = 0; i < hullSize; i++) {
        if (hull[i].x < GRID_SIZE && hull[i].y < GRID_SIZE)
            grid[hull[i].y][hull[i].x] = '#';
    }

    printf("\nVisual Representation of Convex Hull:\n");
    for (int i = GRID_SIZE - 1; i >= 0; i--) { 
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Point points[] = { {0, 0}, {2, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2} };
    int n = sizeof(points) / sizeof(points[0]);

    Point result[MAX_POINTS];
    int hullSize = convexHull(points, n, result);

    printf("\nConvex Hull:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", result[i].x, result[i].y);
    }

    visualizeHull(points, n, result, hullSize);
    return 0;
}




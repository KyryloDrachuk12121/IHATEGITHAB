#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#define MAX_POINTS 1000
#define GRID_SIZE 20  

typedef struct {
    int x, y;
} Point;

extern Point p0;

int compare_points(const void* a, const void* b);
void quicksort(Point arr[], int low, int high, int (*cmp)(const void*, const void*));
double getAngle(Point p0, Point p);
int compare_by_polar_angle(const void* a, const void* b);
void mergeSort(Point arr[], int l, int r, int (*cmp)(const void*, const void*));
int ccw(Point a, Point b, Point c);
int convexHull(Point points[], int n, Point result[]);
void visualizeHull(Point points[], int n, Point hull[], int hullSize);

#endif


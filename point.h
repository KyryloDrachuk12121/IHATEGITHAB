#ifndef POINT_H
#define POINT_H
typedef struct Point {
    int x, y;
} Point;

typedef struct Point* PointPtr;

PointPtr create_point(int x, int y);
void destroy_point(PointPtr p);
int compare_points(const void* a, const void* b);
double slope_to(PointPtr p1, PointPtr p2);

int get_x(PointPtr p);
int get_y(PointPtr p);

#endif

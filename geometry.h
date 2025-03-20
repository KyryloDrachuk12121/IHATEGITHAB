#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct {
    int x, y;
} Point;

void quicksort(Point arr[], int low, int high);
void mergesort(Point arr[], int left, int right);

void print_points(Point points[], int n);

extern Point p0;

#endif 


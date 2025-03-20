#include <stdio.h>
#include <math.h>
#include "geometry.h"

Point p0; 

void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int compare_points(Point a, Point b) {
    if (a.y != b.y)
        return a.y - b.y;
    return a.x - b.x;
}

int partition(Point arr[], int low, int high) {
    Point pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare_points(arr[j], pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(Point arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

double getAngle(Point p0, Point p) {
    return atan2(p.y - p0.y, p.x - p0.x);
}

int compare_by_polar_angle(Point a, Point b) {
    double angleA = getAngle(p0, a);
    double angleB = getAngle(p0, b);
    if (angleA < angleB)
        return -1;
    else if (angleA > angleB)
        return 1;
    else {
        int distA = (a.x - p0.x) * (a.x - p0.x) + (a.y - p0.y) * (a.y - p0.y);
        int distB = (b.x - p0.x) * (b.x - p0.x) + (b.y - p0.y) * (b.y - p0.y);
        return distA - distB;
    }
}

void merge(Point arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare_by_polar_angle(L[i], R[j]) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergesort(Point arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void print_points(Point points[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
}
int main() {
    Point points[] = { {0, 0}, {2, 0}, {1, 1}, {0, 2}, {2, 2}, {1, 3} };
    int n = sizeof(points) / sizeof(points[0]);

    quicksort(points, 0, n - 1);
    printf("Sorted by Y coordinates\n");
    print_points(points, n);

    p0 = points[0];
    mergesort(points + 1, 0, n - 2);
    printf("Sorted by polar angle with respect to {%d, %d}\n", p0.x, p0.y);
    print_points(points, n);

    return 0;
}

#include "point.h"
#include <stdio.h>
#include <stdlib.h>

int compare_by_slope(PointPtr p, PointPtr q, PointPtr reference) {
    double slope1 = slope_to(reference, p);
    double slope2 = slope_to(reference, q);
    if (slope1 < slope2) return -1;
    if (slope1 > slope2) return 1;
    return 0;
}

int compare_by_x(PointPtr p, PointPtr q) {
    return p->x - q->x;
}

void bubble_sort(PointPtr* points, int N, int (*compare)(PointPtr, PointPtr, PointPtr), PointPtr reference) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (compare(points[j], points[j + 1], reference) > 0) {
                PointPtr temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_x(PointPtr* points, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (compare_by_x(points[j], points[j + 1]) > 0) {
                PointPtr temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
}

void print_segment(PointPtr* points, int start, int end) {
    bubble_sort_x(points + start, end - start + 1);
    for (int i = start; i <= end; i++) {
        printf("(%d, %d)", points[i]->x, points[i]->y);
        if (i < end) printf(" -> ");
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    PointPtr* points = (PointPtr*)malloc(N * sizeof(PointPtr));
    for (int i = 0; i < N; i++) {
        int x, y;
        fscanf(file, "%d %d", &x, &y);
        points[i] = create_point(x, y);
    }
    fclose(file);
    for (int i = 0; i < N; i++) {
        bubble_sort(points, N, compare_by_slope, points[i]);
        int start = 0;
        while (start < N - 3) { 
            int end = start + 1;
            while (end < N && slope_to(points[i], points[start]) == slope_to(points[i], points[end])) {
                end++;
            }
            if (end - start >= 3) { 
                print_segment(points, start, end - 1);
            }
            start = end;
        }
    }

    for (int i = 0; i < N; i++) {
        destroy_point(points[i]);
    }
    free(points);

    return 0;
}

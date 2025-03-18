#include "point.h"
#include <stdio.h>
#include <stdlib.h>

int are_collinear(PointPtr p, PointPtr q, PointPtr r, PointPtr s) {
    double slope1 = slope_to(p, q);
    double slope2 = slope_to(p, r);
    double slope3 = slope_to(p, s);
    return slope1 == slope2 && slope2 == slope3;
}

void print_segment(PointPtr p1, PointPtr p2, PointPtr p3, PointPtr p4) {
    printf("(%d, %d) -> (%d, %d) -> (%d, %d) -> (%d, %d)\n",
        get_x(p1), get_y(p1), get_x(p2), get_y(p2),
        get_x(p3), get_y(p3), get_x(p4), get_y(p4));
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
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                for (int l = k + 1; l < N; l++) {
                    if (are_collinear(points[i], points[j], points[k], points[l])) {
                        print_segment(points[i], points[j], points[k], points[l]);
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        destroy_point(points[i]);
    }
    free(points);

    return 0;
}

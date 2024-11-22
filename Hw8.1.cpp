#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    char name[MAX_NAME_LEN];
    int num_points;
    point_t* points;
} polygon_t;

int read_polygon(FILE* file, polygon_t* polygon) {
    if (fgets(polygon->name, MAX_NAME_LEN, file) == NULL) {
        return 0;
    }
    polygon->name[strcspn(polygon->name, "\n")] = 0;

    if (fscanf(file, "%d", &polygon->num_points) != 1) {
        return 0;
    }

    polygon->points = (point_t*)malloc(polygon->num_points * sizeof(point_t));
    if (polygon->points == NULL) {
        return 0;
    }

    for (int i = 0; i < polygon->num_points; i++) {
        if (fscanf(file, "%d %d", &polygon->points[i].x, &polygon->points[i].y) != 2) {
            free(polygon->points);
            return 0;
        }
    }
    return 1;
}

void print_polygon(const polygon_t* polygon) {
    printf("Polygon: %s\n", polygon->name);
    printf("Points: ");
    for (int i = 0; i < polygon->num_points; i++) {
        printf("(%d, %d)", polygon->points[i].x, polygon->points[i].y);
        if (i < polygon->num_points - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main() {
    FILE* file = fopen("polygons.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    polygon_t* polygons = NULL;
    int num_polygons = 0;

    while (1) {
        polygon_t polygon;

        char buffer[200];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (buffer[0] != '\n') {
                fseek(file, -strlen(buffer), SEEK_CUR);
                break;
            }
        }

        if (read_polygon(file, &polygon)) {
            polygon_t* new_polygons = (polygon_t*)malloc((num_polygons + 1) * sizeof(polygon_t));
            if (new_polygons == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(polygons);
                fclose(file);
                return 1;
            }
            for (int i = 0; i < num_polygons; i++) {
                new_polygons[i] = polygons[i];
            }
            new_polygons[num_polygons] = polygon;
            num_polygons++;
            free(polygons);
            polygons = new_polygons;
        }
        else {
            break;
        }
    }

    for (int i = 0; i < num_polygons; i++) {
        print_polygon(&polygons[i]);
        free(polygons[i].points);
    }

    free(polygons);
    fclose(file);
    return 0;
}









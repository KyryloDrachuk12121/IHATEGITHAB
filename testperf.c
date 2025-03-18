#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_SIZES 4
size_t sizes[NUM_SIZES] = { 100, 1000, 10000, 100000 };

int int_comparator(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void insertion_sort(void* array, size_t nitems, size_t size, int (*comp)(const void*, const void*)) {
    char* arr = (char*)array;
    for (size_t i = 1; i < nitems; i++) {
        char* key = malloc(size);
        if (!key) exit(EXIT_FAILURE);
        memcpy(key, arr + i * size, size);

        size_t j = i;
        while (j > 0 && comp(arr + (j - 1) * size, key) > 0) {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        memcpy(arr + j * size, key, size);
        free(key);
    }
}

void selection_sort(void* array, size_t nitems, size_t size, int (*comp)(const void*, const void*)) {
    char* arr = (char*)array;
    for (size_t i = 0; i < nitems - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < nitems; j++) {
            if (comp(arr + j * size, arr + min_idx * size) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            char* temp = malloc(size);
            if (!temp) exit(EXIT_FAILURE);
            memcpy(temp, arr + i * size, size);
            memcpy(arr + i * size, arr + min_idx * size, size);
            memcpy(arr + min_idx * size, temp, size);
            free(temp);
        }
    }
}

void shell_sort(void* array, size_t nitems, size_t size, int (*comp)(const void*, const void*)) {
    char* arr = (char*)array;
    for (size_t gap = nitems / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < nitems; i++) {
            char* temp = malloc(size);
            if (!temp) exit(EXIT_FAILURE);
            memcpy(temp, arr + i * size, size);
            size_t j = i;
            while (j >= gap && comp(arr + (j - gap) * size, temp) > 0) {
                memcpy(arr + j * size, arr + (j - gap) * size, size);
                j -= gap;
            }
            memcpy(arr + j * size, temp, size);
            free(temp);
        }
    }
}

void generate_random_array(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % 100000;
    }
}

void copy_array(int* source, int* dest, size_t size) {
    memcpy(dest, source, sizeof(int) * size);
}

void benchmark() {
    printf("| Sort Algorithm   | Input Size | Random Input Time (s) | Sorted Input Time (s) |\n");
    printf("|------------------|------------|------------------------|------------------------|\n");

    for (int s = 0; s < NUM_SIZES; s++) {
        size_t n = sizes[s];
        int* original = (int*)malloc(n * sizeof(int));
        int* arr = (int*)malloc(n * sizeof(int));

        if (!original || !arr) exit(EXIT_FAILURE);

        generate_random_array(original, n);

        copy_array(original, arr, n);
        clock_t start = clock();
        insertion_sort(arr, n, sizeof(int), int_comparator);
        clock_t end = clock();
        double insertion_random_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        insertion_sort(arr, n, sizeof(int), int_comparator);
        end = clock();
        double insertion_sorted_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("| Insertion Sort   | %10zu | %22.5f | %22.5f |\n", n, insertion_random_time, insertion_sorted_time);

        copy_array(original, arr, n);
        start = clock();
        selection_sort(arr, n, sizeof(int), int_comparator);
        end = clock();
        double selection_random_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        selection_sort(arr, n, sizeof(int), int_comparator);
        end = clock();
        double selection_sorted_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("| Selection Sort   | %10zu | %22.5f | %22.5f |\n", n, selection_random_time, selection_sorted_time);

        copy_array(original, arr, n);
        start = clock();
        shell_sort(arr, n, sizeof(int), int_comparator);
        end = clock();
        double shell_random_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        shell_sort(arr, n, sizeof(int), int_comparator);
        end = clock();
        double shell_sorted_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("| Shell Sort       | %10zu | %22.5f | %22.5f |\n", n, shell_random_time, shell_sorted_time);

        free(original);
        free(arr);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    benchmark();
    return 0;
}



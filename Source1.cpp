#include <stdio.h>
#include <stdlib.h>
#include "Header1.h"

int* create(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        return NULL; 
    }
    return arr;
}
void push_back(int* ptr, int* size, int value) {
    int* new_ptr = (int*)realloc(ptr, (*size + 1) * sizeof(int));
    if (new_ptr == NULL) {
        return;
    }
    ptr = new_ptr;
    ptr[*size] = value;
    (*size)++;
}
void print(const int* ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}
void destroy(int* ptr) {
    free(ptr);
}

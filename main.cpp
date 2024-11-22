#include <stdio.h>
#include <stdlib.h>
#include "Header1.h"

int main() {
    int size;
    int mode;

    printf("Enter the number of rows in the 2D array: ");
    scanf("%d", &size);
    getchar();
    char** arr = allocate_2d_array(size);
    if (!arr) {
        return 1;  
    }
    if (fill_2d_array(arr, size) == -1) {
        free_2d_array(arr, size);  
        return 1;
    }
    printf("Select mode:\n1. Sort characters in the rows\n2. Sort rows \n");
    scanf("%d", &mode);
    printf("\nOriginal array:\n");
    print_2d_array(arr, size);
    if (mode == 1) {
        sort_characters_in_rows(arr, size);
        printf("\nSorted characters in the rows:\n");
        print_2d_array(arr, size);
    }
    else if (mode == 2) {
        sort_rows(arr, size);
        printf("\nSorted rows:\n");
        print_2d_array(arr, size);
    }
    else {
        printf("Invalid mode selected.\n");
    }
    free_2d_array(arr, size);

    return 0;
}


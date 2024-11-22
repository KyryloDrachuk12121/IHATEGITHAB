#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header1.h"

int main() {
    int initial_size;
    int* array = NULL;
    int size;
    srand(time(NULL));
    printf("Enter the initial size of the array: ");
    scanf("%d", &initial_size);
    array = create(initial_size);
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1; 
    }
    size = initial_size;
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 201 - 100;  
    }
    printf("Original array:\n");
    print(array, size);
    int additional_elements = 5; 
    for (int i = 0; i < additional_elements; i++) {
        push_back(array, &size, rand() % 201 - 100); 
    }

    printf("Array after adding new elements:\n");
    print(array, size);
    destroy(array);

    return 0;
}

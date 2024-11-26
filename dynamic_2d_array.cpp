#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header1.h"
char** allocate_2d_array(int size) {
    char** arr = (char**)malloc(size * sizeof(char*));
    if (!arr) {
        perror("Failed to allocate memory for 2D array");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = NULL; 
    }
    return arr;
}
int fill_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter string for row %d: ", i + 1);
        size_t len = 0;
        getline(&arr[i], &len, stdin);  
        arr[i][strcspn(arr[i], "\n")] = '\0';  
    }
    return 0;
}
void print_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}
void sort_rows(char** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {  
                char* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
void sort_characters_in_rows(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        int len = strlen(arr[i]);
        for (int j = 0; j < len - 1; j++) {
            for (int k = j + 1; k < len; k++) {
                if (arr[i][j] > arr[i][k]) {
                    char temp = arr[i][j];
                    arr[i][j] = arr[i][k];
                    arr[i][k] = temp;
                }
            }
        }
    }
}
void free_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);  
    }
    free(arr); 
}









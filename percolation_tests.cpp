#include "percolation.h"
#include <stdio.h>
#include <stdbool.h>

void run_tests();
void test_initialization();
void test_open_coordinate();
void test_vertical_percolation();
void test_horizontal_percolation();
void test_no_diagonal_percolation();
void test_complex_percolation();
void test_open_count();

int main() {
    run_tests();
    return 0;
}

void run_tests() {
    test_initialization();
    test_open_coordinate();
    test_vertical_percolation();
    test_horizontal_percolation();
    test_no_diagonal_percolation();
    test_complex_percolation();
    test_open_count();
}

void test_initialization() {
    Percolation* pc = create_percolation(5);
    printf("Test Initialization: ");
    if (get_opened_count(pc) == 0 && !percolates(pc)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
    destroy_percolation(pc);
}

void test_open_coordinate() {
    Percolation* pc = create_percolation(5);
    open_coordinate(pc, 2, 2);
    printf("Test Open Coordinate: %s\n", is_opened(pc, 2, 2) ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

void test_vertical_percolation() {
    Percolation* pc = create_percolation(5);
    for (int i = 0; i < 5; i++) {
        open_coordinate(pc, i, 2);
    }
    printf("Test Vertical Percolation: %s\n", percolates(pc) ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

void test_horizontal_percolation() {
    Percolation* pc = create_percolation(5);
    for (int j = 0; j < 5; j++) {
        open_coordinate(pc, 2, j);
    }
    printf("Test Horizontal Percolation: %s\n", !percolates(pc) ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

void test_no_diagonal_percolation() {
    Percolation* pc = create_percolation(5);
    for (int i = 0; i < 5; i++) {
        open_coordinate(pc, i, i);
    }
    printf("Test No Diagonal Percolation: %s\n", !percolates(pc) ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

void test_complex_percolation() {
    Percolation* pc = create_percolation(5);
    open_coordinate(pc, 0, 1);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 2, 1);
    open_coordinate(pc, 3, 1);
    open_coordinate(pc, 4, 1);
    printf("Test Complex Percolation: %s\n", percolates(pc) ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

void test_open_count() {
    Percolation* pc = create_percolation(5);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 2, 2);
    open_coordinate(pc, 3, 3);
    printf("Test Open Count: %s\n", get_opened_count(pc) == 3 ? "PASSED" : "FAILED");
    destroy_percolation(pc);
}

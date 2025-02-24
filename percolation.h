#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <stdbool.h>
#include <stdlib.h>
#include "/mnt/c/Users/ruvik/Downloads/dynamic_connectivity/src/dynamic_connectivity.h"


typedef struct {
    int n;
    int opened_count;
    bool* grid;
    DynamicConnectivity dc;  
    int virtual_top;
    int virtual_bottom;
} Percolation;

Percolation* create_percolation(int n);
void destroy_percolation(Percolation* pc);
int get_opened_count(Percolation* pc);
void open_coordinate(Percolation* pc, int i, int j);
bool is_opened(Percolation* pc, int i, int j);
bool percolates(Percolation* pc);

#endif


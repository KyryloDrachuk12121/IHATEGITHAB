#ifndef DYNAMIC_CONNECTIVITY_H
#define DYNAMIC_CONNECTIVITY_H

#include <stdbool.h>

#define CAPACITY 100000

typedef struct {
    int id[CAPACITY];
    int sz[CAPACITY];
} DynamicConnectivity;

void init_dynamic_connectivity(DynamicConnectivity* co, int n);

int root(DynamicConnectivity* co, int i);

bool connected(DynamicConnectivity* co, int p, int q);

void add_union(DynamicConnectivity* co, int p, int q);

#endif 
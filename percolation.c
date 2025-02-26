#include "percolation.h"
#include "../dynamic_connectivity/src/dynamic_connectivity.h"
#include <stdlib.h>

static int index(int n, int i, int j) {
    return i * n + j;
}

Percolation* create_percolation(int n) {
    Percolation* pc = (Percolation*)malloc(sizeof(Percolation));
    if (!pc) return NULL;

    pc->n = n;
    pc->opened_count = 0;
    pc->grid = (bool*)calloc(n * n, sizeof(bool));
    if (!pc->grid) {
        free(pc);
        return NULL;
    }

    init_dynamic_connectivity(&(pc->dc), n * n + 2);
    pc->virtual_top = n * n;
    pc->virtual_bottom = n * n + 1;

    for (int j = 0; j < n; j++) {
        add_union(&(pc->dc), pc->virtual_top, j);
        add_union(&(pc->dc), pc->virtual_bottom, index(n, n - 1, j));
    }

    return pc;
}

void destroy_percolation(Percolation* pc) {
    if (!pc) return;
    free(pc->grid);
    free(pc);
}

int get_opened_count(Percolation* pc) {
    return pc ? pc->opened_count : 0;
}

bool is_opened(Percolation* pc, int i, int j) {
    return pc && pc->grid[index(pc->n, i, j)];
}

void open_coordinate(Percolation* pc, int i, int j) {
    if (!pc || is_opened(pc, i, j)) return;

    int idx = index(pc->n, i, j);
    pc->grid[idx] = true;
    pc->opened_count++;

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    for (int k = 0; k < 4; k++) {
        int ni = i + directions[k][0], nj = j + directions[k][1];
        if (ni >= 0 && ni < pc->n && nj >= 0 && nj < pc->n && is_opened(pc, ni, nj)) {
            add_union(&(pc->dc), idx, index(pc->n, ni, nj));
        }
    }
}

bool percolates(Percolation* pc) {
    return pc && connected(&(pc->dc), pc->virtual_top, pc->virtual_bottom);
}


#include "dynamic_connectivity.h"
#include <stdio.h>

void init_dynamic_connectivity(DynamicConnectivity* co, int n) {
    for (int i = 0; i < n; i++) {
        (*co).id[i] = i;
        (*co).sz[i] = 1;
    }
}

int root(DynamicConnectivity* co, int i) {
    while (i != (*co).id[i]) {
        (*co).id[i] = (*co).id[(*co).id[i]];  // Path compression
        i = (*co).id[i];
    }
    return i;
}

bool connected(DynamicConnectivity* co, int p, int q) {
    return root(co, p) == root(co, q);
}

void add_union(DynamicConnectivity* co, int p, int q) {
    int rootP = root(co, p);
    int rootQ = root(co, q);

    if (rootP == rootQ) return;

    if ((*co).sz[rootP] < (*co).sz[rootQ]) {
        (*co).id[rootP] = rootQ;
        (*co).sz[rootQ] += (*co).sz[rootP];
    }
    else {
        (*co).id[rootQ] = rootP;
        (*co).sz[rootP] += (*co).sz[rootQ];
    }
}


#ifdef DYNAMIC_CONNECTIVITY_MAIN
int main() {
    DynamicConnectivity dc;
    init_dynamic_connectivity(&dc, CAPACITY);  

    int p, q;
    printf("Enter two numbers  -1 -1 to exit:\n");

    while (1) {
        if (scanf("%d %d", &p, &q) != 2) break; 

        if (p == -1 && q == -1) {
            break;
        }

        if (p < 0 || q < 0) {
            printf("Invalid input\n");
            continue;
        }

        if (connected(&dc, p, q)) {
            printf("%d and %d are connected\n", p, q);
        }
        else {
            add_union(&dc, p, q);
            printf("Connected  %d and %d.\n", p, q);
        }
    }

    return 0;
}
#endif



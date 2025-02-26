#include "PercolationStats.h"
#include "percolation.h"
#include "statistical_measures.h"
#include <stdio.h>
#include <stdlib.h>

PercolationStats* create_percolation_stats(int grid_size, int experiments) {
    PercolationStats* ps = (PercolationStats*)malloc(sizeof(PercolationStats));
    if (!ps) return NULL;
    ps->n = grid_size;
    ps->T = experiments;
    ps->thresholds = (double*)malloc(ps->T * sizeof(double));
    if (!ps->thresholds) {
        free(ps);
        return NULL;
    }
    return ps;
}


void destroy_percolation_stats(PercolationStats* ps) {
    if (!ps) return;
    free(ps->thresholds);
    free(ps);
}

void run_experiments(PercolationStats* ps) {
    for (int t = 0; t < ps->T; t++) {
        Percolation* perc = create_percolation(ps->n);
        int opened = 0;
        while (!percolates(perc)) {
            int i = rand() % ps->n;
            int j = rand() % ps->n;
            if (!is_opened(perc, i, j)) {
                open_coordinate(perc, i, j);
                opened++;
            }
        }
        ps->thresholds[t] = (double)opened / (ps->n * ps->n);
        destroy_percolation(perc);
    }
}

double mean_percolation_threshold(PercolationStats* ps) {
    return mean(ps->thresholds, ps->T);
}

double stddev_percolation_threshold(PercolationStats* ps) {
    return stddev(ps->thresholds, ps->T);
}

void print_statistics(PercolationStats* ps) {
    double ci[2];
    confidence_interval(ps->thresholds, ps->T, ci);
    printf("Mean percolation threshold: %lf\n", mean_percolation_threshold(ps));
    printf("Standard deviation: %lf\n", stddev_percolation_threshold(ps));
    printf("95%% confidence interval: [%lf, %lf]\n", ci[0], ci[1]);
}
#include <time.h> // Додаємо для srand()

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <grid_size> <num_experiments>\n", argv[0]);
        return 1;
    }

    int grid_size = atoi(argv[1]);
    int num_experiments = atoi(argv[2]);

    srand(time(NULL)); 

    PercolationStats* ps = create_percolation_stats(grid_size, num_experiments);
    if (!ps) {
        printf("Memory allocation failed\n");
        return 1;
    }

    run_experiments(ps);
    print_statistics(ps);
    destroy_percolation_stats(ps);

    return 0;
}


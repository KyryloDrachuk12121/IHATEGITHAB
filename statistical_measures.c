#include "statistical_measures.h"
#include <math.h>

double mean(double* experiments, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }
    return sum / n;
}

double stddev(double* experiments, int n) {
    if (n <= 1) return 0.0; 
    double m = mean(experiments, n);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += (experiments[i] - m) * (experiments[i] - m);
    }
    return sqrt(sum_sq_diff / (n - 1)); 
}

void confidence_interval(double* experiments, int n, double* ci) {
    double m = mean(experiments, n);
    double sd = stddev(experiments, n);
    double margin = 1.96 * (sd / sqrt(n));
    ci[0] = m - margin;
    ci[1] = m + margin;
}


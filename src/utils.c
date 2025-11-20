#include "utils.h"
double elapsed_ms(struct timespec start, struct timespec end) {
    double s = (end.tv_sec - start.tv_sec) * 1000.0;
    double ns = (end.tv_nsec - start.tv_nsec) / 1e6;
    return s + ns;
}

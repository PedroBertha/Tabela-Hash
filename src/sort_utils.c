#include "sort_utils.h"
#include <stdlib.h>
#include <string.h>

/* Comparator para strings (char*) */
int compare_cstrings(const void *a, const void *b) {
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    return strcmp(sa, sb);
}

/* Wrapper simples para usar qsort com array de void* */
void qsort_generic(void **array, size_t n, int (*cmp)(const void*, const void*)) {
    qsort(array, n, sizeof(void*), (int (*)(const void*, const void*))cmp);
}

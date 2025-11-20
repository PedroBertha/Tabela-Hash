#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <stddef.h>   // <-- IMPORTANTE! resolve o erro do size_t

/* comparator for qsort on char* */
int compare_cstrings(const void *a, const void *b);

/* generic qsort wrapper for array of void* (strings here) */
void qsort_generic(void **array, size_t n, int (*cmp)(const void*, const void*));

#endif

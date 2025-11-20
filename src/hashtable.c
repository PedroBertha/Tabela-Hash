#define _POSIX_C_SOURCE 200809L
#include "hashtable.h"
#include "sort_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned int hash_func(const char *s, size_t m)
{
    unsigned long hash = 2166136261u; // FNV offset basis
    while (*s)
    {
        hash ^= (unsigned char)(*s);
        hash *= 16777619u;            // FNV prime
        s++;
    }
    return (unsigned int)(hash % m);
}

HashTable *ht_create(size_t m) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->m = m;
    ht->total = 0;
    ht->buckets = calloc(m, sizeof(DList*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    for (size_t i = 0; i < m; ++i) ht->buckets[i] = dlist_create();
    return ht;
}

void ht_free(HashTable *ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->m; ++i) {
        dlist_free(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

void ht_insert(HashTable *ht, const char *nome) {
    if (!ht || !nome) return;
    unsigned int idx = hash_func(nome, ht->m);
    dlist_push_back(ht->buckets[idx], nome);
    ht->total++;
}

int ht_contains(HashTable *ht, const char *nome) {
    if (!ht || !nome) return 0;
    unsigned int idx = hash_func(nome, ht->m);
    return dlist_contains(ht->buckets[idx], nome);
}

int ht_remove(HashTable *ht, const char *nome) {
    if (!ht || !nome) return 0;
    unsigned int idx = hash_func(nome, ht->m);
    int removed = dlist_remove(ht->buckets[idx], nome);
    if (removed) ht->total--;
    return removed;
}

size_t ht_bucket_count(HashTable *ht, size_t i) {
    if (!ht || i >= ht->m) return 0;
    return ht->buckets[i]->count;
}

void ht_fill_counts(HashTable *ht, size_t *counts) {
    if (!ht || !counts) return;
    for (size_t i = 0; i < ht->m; ++i) counts[i] = ht->buckets[i]->count;
}

void ht_sort_bucket(HashTable *ht, size_t i) {
    if (!ht || i >= ht->m) return;
    size_t n = ht->buckets[i]->count;
    if (n <= 1) return;
    size_t arr_n = 0;
    char **arr = dlist_to_array(ht->buckets[i], &arr_n);
    if (!arr) return;
    qsort_generic((void **)arr, arr_n, compare_cstrings);
    /* rebuild the list: free existing list and re-insert sorted items */
    dlist_free(ht->buckets[i]);
    ht->buckets[i] = dlist_create();
    for (size_t k = 0; k < arr_n; ++k) {
        dlist_push_back(ht->buckets[i], arr[k]);
        free(arr[k]);
    }
    free(arr);
}

int ht_export_counts_csv(HashTable *ht, const char *path) {
    if (!ht || !path) return 0;
    FILE *f = fopen(path, "w");
    if (!f) return 0;
    fprintf(f, "bucket,count\n");
    for (size_t i = 0; i < ht->m; ++i) {
        fprintf(f, "%zu,%zu\n", i, ht->buckets[i]->count);
    }
    fclose(f);
    return 1;
}

void ht_find_position(HashTable *ht, const char *nome, int *bucket, int *pos) {
    size_t b = hash_func(nome, ht->m);
    *bucket = (int)b;

    int index = 0;
    DNode *cur = ht->buckets[b]->head;

    while (cur)
    {
        if (strcmp(cur->nome, nome) == 0)
        {
            *pos = index;
            return;
        }
        cur = cur->next;
        index++;
    }

    *bucket = -1;
    *pos = -1;
}
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include "dlist.h"

typedef struct HashTable {
    DList **buckets; /* array de ponteiros para DList */
    size_t m;        /* numero de chaves */
    size_t total;    /* total de elementos */
} HashTable;

/* cria tabela com m buckets */
HashTable *ht_create(size_t m);

/* libera tabela */
void ht_free(HashTable *ht);

/* função hash (implementada em hashtable.c) */
/* insere (copia nome internamente) */
void ht_insert(HashTable *ht, const char *nome);

/* procura se existe; retorna 1 se existe */
int ht_contains(HashTable *ht, const char *nome);

/* remove (retorna 1 se removido) */
int ht_remove(HashTable *ht, const char *nome);

/* retorna quantidade no bucket i */
size_t ht_bucket_count(HashTable *ht, size_t i);

/* preenche array counts (caller aloca counts com tamanho ht->m) */
void ht_fill_counts(HashTable *ht, size_t *counts);

/* ordena bucket i (usa quicksort via sort_utils) */
void ht_sort_bucket(HashTable *ht, size_t i);

/* exporta counts to CSV (path) */
int ht_export_counts_csv(HashTable *ht, const char *path);

void ht_find_position(HashTable *ht, const char *nome, int *bucket, int *pos);

size_t ht_hash(const char *key);

#endif

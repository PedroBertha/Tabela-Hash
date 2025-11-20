#define _POSIX_C_SOURCE 200809L
#include "dlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

DList *dlist_create(void) {
    DList *l = malloc(sizeof(DList));
    if (!l) return NULL;
    l->head = l->tail = NULL;
    l->count = 0;
    return l;
}

static char *strdup_safe(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s, n + 1);
    return p;
}

void dlist_push_back(DList *list, const char *nome) {
    if (!list || !nome) return;
    DNode *n = malloc(sizeof(DNode));
    n->nome = strdup_safe(nome);
    n->next = NULL;
    n->prev = list->tail;
    if (list->tail) list->tail->next = n;
    list->tail = n;
    if (!list->head) list->head = n;
    list->count++;
}

int dlist_remove(DList *list, const char *nome) {
    if (!list || !nome) return 0;
    DNode *cur = list->head;
    while (cur) {
        if (strcmp(cur->nome, nome) == 0) {
            if (cur->prev) cur->prev->next = cur->next;
            else list->head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else list->tail = cur->prev;
            free(cur->nome);
            free(cur);
            list->count--;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int dlist_contains(DList *list, const char *nome) {
    if (!list || !nome) return 0;
    DNode *cur = list->head;
    while (cur) {
        if (strcmp(cur->nome, nome) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

char **dlist_to_array(DList *list, size_t *out_count) {
    if (!list) {
        if (out_count) *out_count = 0;
        return NULL;
    }
    size_t n = list->count;
    char **arr = malloc(sizeof(char*) * n);
    if (!arr) {
        *out_count = 0;
        return NULL;
    }
    DNode *cur = list->head;
    size_t i = 0;
    while (cur) {
        arr[i++] = strdup_safe(cur->nome);
        cur = cur->next;
    }
    if (out_count) *out_count = n;
    return arr;
}

void dlist_free(DList *list) {
    if (!list) return;
    DNode *cur = list->head;
    while (cur) {
        DNode *tmp = cur->next;
        free(cur->nome);
        free(cur);
        cur = tmp;
    }
    free(list);
}

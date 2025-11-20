#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct DNode {
    char *nome;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct DList {
    DNode *head;
    DNode *tail;
    size_t count;
} DList;

/* cria lista vazia */
DList *dlist_create(void);

/* libera lista e todos os nós */
void dlist_free(DList *list);

/* insere no final (mantém duplicatas) */
void dlist_push_back(DList *list, const char *nome);

/* remove primeiro nó que bate com nome; retorna 1 se removido */
int dlist_remove(DList *list, const char *nome);

/* procura e retorna 1 se existe */
int dlist_contains(DList *list, const char *nome);

/* transfere conteúdo para vetor (aloca vetor de char* e escreve *out_count) */
/* o array retornado deve ser liberado pelo chamador (cada string free) */
char **dlist_to_array(DList *list, size_t *out_count);

#endif

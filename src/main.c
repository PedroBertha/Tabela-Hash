#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashtable.h"
#include "utils.h"

void mostrar_estatisticas(HashTable *ht)
{
    size_t total_buckets = ht->m;
    size_t total_elementos = ht->total;

    size_t min = (size_t)-1;
    size_t max = 0;
    size_t soma = 0;

    size_t bucket_min = 0;
    size_t bucket_max = 0;

    for (size_t i = 0; i < ht->m; i++)
    {
        size_t c = ht->buckets[i]->count;
        soma += c;

        if (c < min)
        {
            min = c;
            bucket_min = i;
        }

        if (c > max)
        {
            max = c;
            bucket_max = i;
        }
    }

    double media = (double)soma / total_buckets;

    printf("\n===== ESTATÍSTICAS DA TABELA HASH =====\n");
    printf("Total de buckets: %zu\n", total_buckets);
    printf("Total de elementos: %zu\n", total_elementos);
    printf("Fator de carga (load factor): %.2f\n", media);
    printf("Bucket mais cheio: #%zu (%zu elementos)\n", bucket_max, max);
    printf("Bucket mais vazio: #%zu (%zu elementos)\n", bucket_min, min);
    printf("========================================\n\n");
}

void menu(HashTable *ht)
{
    int opcao = 0;
    char buffer[256];

    while (1)
    {
        printf("\n=========== MENU ===========\n");
        printf("1 - Pesquisar nome\n");
        printf("2 - Inserir nome\n");
        printf("3 - Remover nome\n");
        printf("4 - Mostrar bucket\n");
        printf("5 - Sair\n");
        printf("6 - Estatísticas da tabela hash\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n

        if (opcao == 1)
        {
            printf("\nDigite o nome para pesquisar: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            int bucket = -1;
            int pos = -1;
            ht_find_position(ht, buffer, &bucket, &pos);

            if (bucket == -1)
            {
                printf("Resultado: NAO ENCONTRADO\n");
            }
            else
            {
                printf("ENCONTRADO no bucket %d, posicao %d\n", bucket, pos);
            }
        }

        else if (opcao == 2)
        {
            printf("\nDigite o nome para inserir: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            ht_insert(ht, buffer);
            printf("Inserido com sucesso.\n");
        }

        else if (opcao == 3)
        {
            printf("\nDigite o nome para remover: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            printf("%s\n",
                   ht_remove(ht, buffer) ? "Removido." : "Nao encontrado.");
        }

        else if (opcao == 4)
        {
            unsigned int b;
            printf("\nDigite o numero do bucket (0 a %u): ", (unsigned int)(ht->m - 1));
            scanf("%u", &b);
            getchar();

            if (b >= ht->m)
            {
                printf("Bucket invalido!\n");
                continue;
            }

            printf("\n--- Bucket %u ---\n", b);
            printf("Bucket %u tem %zu elementos.\n", b, ht->buckets[b]->count);

            DNode *cur = ht->buckets[b]->head;
            int pos = 0;

            while (cur)
            {
                printf("[%d] %s\n", pos, cur->nome);
                cur = cur->next;
                pos++;
            }
        }

        else if (opcao == 6)
        {
            mostrar_estatisticas(ht);
        }

        else if (opcao == 5)
        {
            printf("Saindo...\n");
            break;
        }

        else
        {
            printf("Opcao invalida.\n");
        }
    }
}
// ---------- FIM DO MENU ----------

int main(int argc, char **argv)
{
    const char *path = "data/nomes.txt";
    if (argc >= 2)
        path = argv[1];

    FILE *f = fopen(path, "r");
    if (!f)
    {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", path);
        return 1;
    }

    size_t m = 53;
    HashTable *ht = ht_create(m);

    if (!ht)
    {
        fprintf(stderr, "Erro alocando tabela hash\n");
        fclose(f);
        return 1;
    }

    char line[256];
    size_t inserted = 0;

    clock_t start = clock();

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0)
            continue;

        ht_insert(ht, line);
        inserted++;
    }

    fclose(f);

    double ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("Lidos e inseridos: %zu nomes\n", inserted);
    printf("Tempo insercao: %.3f ms\n", ms);

    ht_export_counts_csv(ht, "out/counts.csv");
    printf("Counts exportados para out/counts.csv\n");

    // --- MENU INTERATIVO ---
    menu(ht);

    ht_free(ht);
    return 0;
}

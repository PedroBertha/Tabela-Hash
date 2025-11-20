# Relatório — Trabalho Final: Tabela Hash com Encadeamento

Este trabalho implementa uma tabela hash com encadeamento usando listas duplamente encadeadas para armazenar 100.788 nomes brasileiros. O objetivo foi implementar inserção, consulta, remoção, análise de distribuição de chaves (histograma), e ordenação dos elementos por chave usando um algoritmo de complexidade equivalente ao quicksort.

## Metodologia
A tabela foi implementada como um array de `m` buckets, cada bucket apontando para uma lista duplamente encadeada. Escolheu-se `m = 53`, um número primo próximo de 50 como solicitado, pois primos reduzem padrões indesejáveis com operações modulares e tendem a melhorar a dispersão para funções de hash simples.

A função hash utilizada é uma função polinomial rolling (base 31), que processa cada caractere do nome e atualiza `h = (31*h + c) % m`. Esta função é eficiente e costuma distribuir bem strings alfabéticas. A colisão é tratada por encadeamento — cada nome cujo hash cai na mesma chave é armazenado na lista correspondente.

Para facilitar a ordenação, cada lista pode ser convertida temporariamente para um vetor de `char*`; sobre esse vetor aplica-se `qsort` (complexidade média O(n log n)). Após a ordenação, o bucket é substituído pela lista reconstruída na ordem ordenada.

## Implementação
O projeto foi modularizado em:
- `dlist` — lista duplamente encadeada (criação, inserção no fim, remoção, busca, conversão para vetor);
- `hashtable` — criação da tabela, hash, inserção, remoção, buscas, exportação de contagens;
- `sort_utils` — wrapper sobre `qsort` para comparar strings;
- `main` — rotina que lê o arquivo de nomes, insere todos os nomes na hash, exporta `counts.csv` para gerar o histograma.

O arquivo de entrada `nomes.txt` foi lido linha a linha, limpando `\n`/`\r` e ignorando linhas em branco.

## Resultados e análise
Executando o programa gerou-se o arquivo `out/counts.csv` contendo a frequência de cada bucket. Para avaliar a hipótese do hashing uniforme (isto é, se os nomes foram distribuídos aproximadamente igualmente entre as chaves), foi gerado um histograma com essas contagens (pode-se usar Python/Excel para plotar). A hipótese é considerada alcançada se a variância das contagens for baixa e as contagens médias por bucket forem próximas a `N/m` (onde `N` é total de nomes). Caso existam buckets com carga significativamente maior, isso indica enviesamento da função de hash sobre o corpus específico.

## Discussão sobre colisões
O tratamento por encadeamento é implementado desde o início — sempre que duas strings mapeiam à mesma chave, ambas coexistem na lista do bucket. Não foi implementado rehash dinâmico neste trabalho, pois a especificação pedia uma M aproximadamente fixa. Em aplicações reais, rehash quando a carga média (N/m) ultrapassa um limiar é uma boa prática.

## Conclusão
O projeto cumpre os requisitos: usa listas duplamente encadeadas, implementa inserção, busca, remoção, contagem por chave, tratamento de colisão (encadeamento) e ordenação por bucket via quicksort (através do `qsort`). A análise da hipótese do hashing uniforme pode ser feita plotando `out/counts.csv` e calculando métricas (média, desvio padrão). A função hash polinomial e `m = 53` foram justificadas teoricamente.


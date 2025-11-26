RELATÓRIO FINAL – TABELA HASH COM ENCADEAMENTO

Este trabalho teve como objetivo implementar uma tabela hash utilizando obrigatoriamente listas duplamente encadeadas, conforme solicitado, e avaliar seu comportamento utilizando uma base de 100.788 nomes brasileiros. O foco principal foi analisar a distribuição dos elementos entre os buckets, avaliar a necessidade e eficácia de técnicas de tratamento de colisão e verificar se a hipótese do hashing uniforme foi atingida. Além disso, foram realizados testes experimentais variando o tamanho da tabela hash para valores próximos de 50, conforme as orientações.

Lista Encadeada Dupla
A estrutura de dados escolhida para armazenar os nomes dentro de cada bucket foi a lista duplamente encadeada. Esse tipo de lista permite:

Inserção eficiente no final

Remoção eficiente de qualquer posição

Navegação nos dois sentidos

Manipulação simples dos nós mesmo com colisões frequentes

Essa estrutura cumpre os requisitos do trabalho e torna a manipulação dos itens dentro de cada bucket eficiente mesmo quando ocorrem colisões.

As seguintes operações foram implementadas:

Inserção de nomes

Busca / consulta

Remoção

Obtenção da quantidade de elementos por bucket

Conversão do bucket para vetor

Ordenação dos nomes com Quicksort

Exportação dos dados para arquivos CSV

Avaliação da tabela hash gerada e hipótese do hashing uniforme

A hipótese do hashing uniforme afirma que todos os elementos têm a mesma probabilidade de cair em qualquer bucket, resultando em uma distribuição equilibrada.

Utilizando a função FNV-1a, que é conhecida pela boa dispersão em strings, obtivemos distribuições bastante uniformes. Nos testes com M igual a 53 e 59, observou-se que:

Não houve buckets extremamente sobrecarregados

As quantidades por chave mantiveram-se próximas à média

O spread (diferença entre o maior e o menor bucket) foi baixo em todos os casos

A uniformidade melhorou conforme M aumentou

Isso mostra que a função hash escolhida atende bem ao princípio da dispersão uniforme.

d) Análise dos histogramas

Os histogramas mostram a quantidade de elementos em cada bucket. A partir dos dados:

M = 53: espalhamento razoável, com spread de 177

<img width="540" height="324" alt="image" src="https://github.com/user-attachments/assets/9d5f4d13-c127-4a09-a374-b8cd48f03137" />

M = 59: melhor uniformidade e spread menor (165)

<img width="533" height="317" alt="image" src="https://github.com/user-attachments/assets/8a0fb7df-fb30-415c-81ce-628ea0181a6b" />

Os gráficos indicam que não há concentração excessiva em nenhum bucket específico. A curva se mantém estável e próxima da média, evidenciando um bom comportamento do hashing.

Ordenação dos elementos
Os elementos de um bucket possam ser ordenados usando Quicksort ou algoritmo equivalente com complexidade 𝑂 ( 𝑛 log ⁡ 𝑛 ) O(nlogn). Para isso, foi implementado um método que:

Converte o bucket para um vetor

Aplica qsort() da biblioteca padrão (que utiliza QuickSort/IntroSort)

Reconstrói a lista ordenada

Assim, o requisito de ordenação foi totalmente atendido.

Hashing com Encadeamento
Toda a tabela foi construída utilizando encadeamento, conforme item obrigatório do trabalho. Cada bucket contém uma DList*, garantindo que múltiplos elementos possam ocupar o mesmo índice sem perda de dados.

Base de Dados Utilizada
Foi utilizada a base fornecida pelo professor contendo 100.788 nomes brasileiros, garantindo adequação ao requisito e permitindo uma análise estatística realista.


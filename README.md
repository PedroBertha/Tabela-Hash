RELATÓRIO FINAL – TABELA HASH COM ENCADEAMENTO

Este trabalho teve como objetivo implementar uma tabela hash utilizando obrigatoriamente listas duplamente encadeadas, conforme solicitado, e avaliar seu comportamento utilizando uma base de 100.788 nomes brasileiros. O foco principal foi analisar a distribuição dos elementos entre os buckets, avaliar a necessidade e eficácia de técnicas de tratamento de colisão e verificar se a hipótese do hashing uniforme foi atingida. Além disso, foram realizados testes experimentais variando o tamanho da tabela hash para valores próximos de 50, conforme as orientações.

1. Lista Encadeada Dupla

A estrutura de dados escolhida para armazenar os nomes dentro de cada bucket foi a lista duplamente encadeada, conforme exigido. Esse tipo de lista permite:

Inserção eficiente no final

Remoção eficiente de qualquer posição

Navegação nos dois sentidos

Manipulação simples dos nós mesmo com colisões frequentes

Essa estrutura cumpre os requisitos do trabalho e torna a manipulação dos itens dentro de cada bucket eficiente mesmo quando ocorrem colisões.

2. Operações Implementadas

As seguintes operações foram implementadas:

Inserção de nomes

Busca / consulta

Remoção

Obtenção da quantidade de elementos por bucket

Conversão do bucket para vetor

Ordenação dos nomes com Quicksort

Exportação dos dados para arquivos CSV

Todas foram desenvolvidas seguindo boas práticas e garantindo comportamento correto mesmo com grande quantidade de colisões.

3. Tratamento de Colisão
a) Quando deveria ser implementado tratamento de colisão?

O tratamento de colisão é necessário em qualquer tabela hash quando dois ou mais elementos mapeiam para o mesmo índice. Isso é inevitável quando:

O conjunto de dados é grande (como a base de 100k nomes)

O valor de M é significativamente menor do que a quantidade total

A função hash pode gerar colisões naturais devido à natureza dos dados

Portanto, implementar tratamento de colisão é fundamental para evitar perda de dados e garantir a integridade da tabela.

b) Como poderia ser essa implementação?

Duas técnicas comuns são:

Endereçamento aberto

Encadeamento

O trabalho exigiu explicitamente o uso de encadeamento, onde cada bucket contém uma lista (neste caso, duplamente encadeada) que armazena todos os elementos que colidiram naquele índice. Essa solução foi implementada integralmente.

c) Avaliação da tabela hash gerada e hipótese do hashing uniforme

A hipótese do hashing uniforme afirma que todos os elementos têm a mesma probabilidade de cair em qualquer bucket, resultando em uma distribuição equilibrada.

Utilizando a função FNV-1a, que é conhecida pela boa dispersão em strings, obtivemos distribuições bastante uniformes. Nos testes com M igual a 53, 59 e 71, observou-se que:

Não houve buckets extremamente sobrecarregados

As quantidades por chave mantiveram-se próximas à média

O spread (diferença entre o maior e o menor bucket) foi baixo em todos os casos

A uniformidade melhorou conforme M aumentou

Isso mostra que a função hash escolhida atende bem ao princípio da dispersão uniforme.

d) Análise dos histogramas

Os histogramas mostram a quantidade de elementos em cada bucket. A partir dos dados:

M = 53: espalhamento razoável, com spread de 177

M = 59: melhor uniformidade e spread menor (165)

M = 71: melhor caso testado, com spread de 159 e buckets muito próximos entre si

Os gráficos indicam que não há concentração excessiva em nenhum bucket específico. A curva se mantém estável e próxima da média, evidenciando um bom comportamento do hashing.

4. Ordenação dos elementos

O trabalho exige que os elementos de um bucket possam ser ordenados usando Quicksort ou algoritmo equivalente com complexidade 
𝑂
(
𝑛
log
⁡
𝑛
)
O(nlogn). Para isso, foi implementado um método que:

Converte o bucket para um vetor

Aplica qsort() da biblioteca padrão (que utiliza QuickSort/IntroSort)

Reconstrói a lista ordenada

Assim, o requisito de ordenação foi totalmente atendido.

5. Hashing com Encadeamento

Toda a tabela foi construída utilizando encadeamento, conforme item obrigatório do trabalho. Cada bucket contém uma DList*, garantindo que múltiplos elementos possam ocupar o mesmo índice sem perda de dados.

6. Base de Dados Utilizada

Foi utilizada a base fornecida pelo professor contendo 100.788 nomes brasileiros, garantindo adequação ao requisito e permitindo uma análise estatística realista.

7. Escolha do valor de M

O trabalho exige que M seja aproximadamente 50. Foram testados:

M = 53

M = 59

M = 71

Todos são números primos, o que reduz padrões e melhora a dispersão. Após testes e análise dos histogramas, concluiu-se que M = 71 apresentou a melhor distribuição.

A justificativa teórica:

números primos reduzem colisões por padrões comuns em strings

evitam que a função hash caia em alinhamentos desfavoráveis

melhoram o espalhamento estatístico

8. Hipótese do Hashing Uniforme

Com base nas análises e histogramas, conclui-se que:

✔ Sim, a hipótese do hashing uniforme foi praticamente alcançada.

A distribuição mostrou:

baixa variabilidade

ausência de buckets com sobrecarga extrema

média muito estável

espalhamento próximo do ideal

9. Histograma e interpretação

Os histogramas demonstram visualmente como os valores foram distribuídos por bucket. Observações:

Os buckets apresentam quantidades próximas entre si

Não há picos isolados

A função FNV-1a distribuiu os nomes de forma eficiente

M = 71 apresentou o comportamento mais uniforme

Isso confirma a qualidade da função hash e da abordagem de encadeamento.

<img width="540" height="324" alt="image" src="https://github.com/user-attachments/assets/9d5f4d13-c127-4a09-a374-b8cd48f03137" />

<img width="533" height="317" alt="image" src="https://github.com/user-attachments/assets/8a0fb7df-fb30-415c-81ce-628ea0181a6b" />



# Como Usar
O código principal está em index.c 
para transformá-lo em executável:
```bash
$ gcc index.c -o index
```
como utilizá-lo:
``` bash
$ ./index <N> <Np> <Nc>
N = tamanho do buffer
Np = numero de produtores
Nc = numero de consumidores
```
Outros executáveis e arquivos:

executor.sh --> serve para variar os parâmtros de tamanho do buffer, número de produtores e número de consumidorers. Deve ser executada na mesma pasta onde está o executável de index.c

analise de gráficos --> faz o plot de gráficos para a análise de dados da tabela gerada por meio dos resultados de executor.sh, nomeada de dados_produtor_consumidor_tempo_de_execucao.csv

vários gráficos foram gerados de acordo com o tamanho do buffer
# Produtor Consumidor

Implemente um programa Produtor-Consumidor multithreaded com memória compartilhada. Assuma que a memória compartilhada é um vetor de
números inteiros de tamanho N. O número de threads do tipo produtor
e consumidor são parâmetros do programa dados por Np e Nc, respectivamente. A thread produtor deve gerar números inteiros aleatórios entre 1 e
`10^7`
e colocar o número em uma posição livre da memória compartilhada. A
thread consumidor deve retirar um número produzido por um produtor da
memória compartilhada, liberar a posição do vetor, e verificar se o mesmo é
primo, imprimindo o resultado no terminal.

Repare que a memória compartilhada será escrita e lida por várias threads, então o acesso deve ser serializado, evitando efeitos indesejáveis da
condição de corrida. Utilize semáforos para serializar o acesso à memória
compartilhada. Repare ainda que quando a memória compartilhada estiver
cheia ou vazia, as threads produtor ou consumidor devem aguardar bloqueadas, respectivamente. Ou seja, uma thread produtor aguarda até que haja
uma posição de memória livre, e uma thread consumidor aguarda até que
haja uma posição de memória ocupada. Utilize semáforos contadores para
esta coordenação, como visto em aula.

Para o estudo de caso, considere que o programa termina sua execução
após o consumidor processar M = 105 números. Considere ainda os valores
N = 1, 10, 100, 1000, com os seguintes combinações de número de threads
produtor/consumidor:

`(Np, Nc) ∈ {(1, 1),(1, 2),(1, 4),(1, 8),(2, 1),(4, 1),(8, 1)}.`

Para cada combinação de parâmetros, obtenha o tempo de execução do
seu programa, rodando o programa 10 vezes para calcular o tempo médio
de execução. Apresente um gráfico mostrando o tempo médio de execução
em função do número de threads produtor/consumidor para cada valor de N
(cada N deve ser uma curva no gráfico). Analise o comportamento observado.

Para cada cenário, trace um gráfico representativo com a ocupação do
buffer compartilhado ao longo do tempo. Para gerar o gráfico, utilize um
vetor que armazena a ocupação do buffer após cada operação de produção
ou consumo. Ao final, use o vetor para gerar o gráfico (ou arquivo).

O que você pode concluir em cada um dos casos?



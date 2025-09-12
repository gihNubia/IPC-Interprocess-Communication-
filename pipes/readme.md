# Pipes

Implemente o programa Produtor-Consumidor como vimos em aula com dois
processos que utilizam pipes (anonymous pipes, para ser mais preciso) para
fazer a comunicação.

O programa produtor deve gerar números inteiros aleatórios e crescentes,
da seguinte forma:

`Ni = N(i−1) + ∆, N0 = 1, ∆ ∈ [1, 100] `

O programa consumidor deve receber o número e verificar se o mesmo
é primo, imprimindo o resultado no terminal. Seu programa deve primeiramente criar um pipe e depois fazer um `fork()` para duplicar o processo, de
forma que os dois processos (pai e filho) tenham as duas respectivas pontas
do pipe _(write end e read end)_.

O processo consumidor deve terminar quando receber o número 0. O programa produtor tem como parâmetro o número de números a serem gerados
(ex.: 1000), depois do qual o número zero é enviado, e o produtor termina
sua execução.

Cuidado com a representação numérica ao escrever no pipe!

Dica: converta o número para uma string de tamanho fixo, por exemplo,
20 bytes. Escreva e leia do pipe este mesmo número de bytes para cada
mensagem.

Teste o seu programa mostrando seu funcionamento para alguns casos.

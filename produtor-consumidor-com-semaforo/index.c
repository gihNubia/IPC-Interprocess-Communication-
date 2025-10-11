#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUMBER 10000000
#define M 100000  
#define RUNS 10

int *buffer;
int N;              
int Np;
int Nc;
int in = 0;         // Índice produtores
int out = 0;        // Índice consumidores
int count_consumed = 0;  // Total consumido

// Semáforos
sem_t empty;  
sem_t full;   
pthread_mutex_t mutex;  

// Primo
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i*i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// produtor
void* producer(void* arg) {
    while (1) {
        int num = rand() % MAX_NUMBER + 1; // Gera número aleatório entre 1 e 10^7

        sem_wait(&empty); // Aguarda posição vazia
        pthread_mutex_lock(&mutex);

        buffer[in] = num;
        in = (in + 1) % N;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);  // Indica que há um item cheio
    }
    return NULL;
}

// consumidor
void* consumer(void* arg) {
    while (1) {
        sem_wait(&full); // Aguarda posição cheia
        pthread_mutex_lock(&mutex);

        if (count_consumed >= M) {
            pthread_mutex_unlock(&mutex);
            sem_post(&full); // Liberar para outras threads
            break;
        }

        int num = buffer[out];
        out = (out + 1) % N;
        count_consumed++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Indica posição livre

        // primo
        if (is_prime(num)) {
            printf("%d --> primo\n", num);
        } else {
            printf("%d --> não é primo\n", num);
        }
    }
    return NULL;
}

int cicle(int N, int Nc, int Np) {

    srand(time(NULL));

    buffer = malloc(N * sizeof(int));
    pthread_t producers[Np], consumers[Nc];

    // Inicializa 
    sem_init(&empty, 0, N); 
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Cria produtor
    for (int i = 0; i < Np; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    // Cria consumidor
    for (int i = 0; i < Nc; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Aguarda fim consumidor
    for (int i = 0; i < Nc; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Cancela threads produtoras, pois consumidores já processaram M números
    for (int i = 0; i < Np; i++) {
        pthread_cancel(producers[i]);
        pthread_join(producers[i], NULL);
    }

    // Destrói semáforos e mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    free(buffer);

    printf("Processamento concluído. Total de números consumidos: %d\n", count_consumed);
    
}

int main(int argc, char *argv[]) {

    printf("\nTamanho do buffer (N):");
    scanf("%d", &N);

    printf("\nNumero de produtores (Np): ");
    scanf("%d", &Np);

    printf("\nNumero de Consumidores (Nc): ");
    scanf("%d", &Nc);

    clock_t begin = clock();

    for (int i = 0; i < RUNS; i++) {
        cicle(N, Nc, Np);
    }

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    double average = time_spent / RUNS;

    printf("Tempo médio de execução: %.5f segundos", average);
    return 0;
}
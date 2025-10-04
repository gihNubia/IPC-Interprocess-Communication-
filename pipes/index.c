#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>

#define TAM_MSG 20

static void abortar(const char *mensagem)
{
    perror(mensagem);
    exit(EXIT_FAILURE);
}

static ssize_t escrever_tudo(int descritor, const void *buffer, size_t n)
{
    size_t restante = n;
    const char *ptr = (const char *)buffer;
    while (restante > 0)
    {
        ssize_t escrito = write(descritor, ptr, restante);
        if (escrito < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }
        restante -= (size_t)escrito;
        ptr += escrito;
    }
    return (ssize_t)n;
}

static ssize_t ler_tudo(int descritor, void *buffer, size_t n)
{
    size_t restante = n;
    char *ptr = (char *)buffer;
    while (restante > 0)
    {
        ssize_t lido = read(descritor, ptr, restante);
        if (lido == 0)
            break;
        if (lido < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        }
        restante -= (size_t)lido;
        ptr += lido;
    }
    return (ssize_t)(n - restante);
}

static int eh_primo(uint64_t x)
{
    if (x < 2)
        return 0;
    if (x % 2 == 0)
        return x == 2;
    if (x % 3 == 0)
        return x == 3;
    for (uint64_t i = 5; i * i <= x; i += 6)
    {
        if (x % i == 0 || x % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <QTD_NUMEROS>\n", argv[0]);
        return EXIT_FAILURE;
    }
    long quantidade = strtol(argv[1], NULL, 10);
    if (quantidade < 0)
    {
        fprintf(stderr, "QTD_NUMEROS deve ser >= 0\n");
        return EXIT_FAILURE;
    }

    int descritores[2];
    if (pipe(descritores) < 0)
        abortar("pipe");

    pid_t pid = fork();
    if (pid < 0)
        abortar("fork");

    if (pid == 0)
    {
        close(descritores[1]);
        char buffer[TAM_MSG];
        for (;;)
        {
            ssize_t lido = ler_tudo(descritores[0], buffer, TAM_MSG);
            if (lido == 0)
                break;
            if (lido < 0)
                abortar("read");
            if (lido != TAM_MSG)
                break;
            char str_num[TAM_MSG + 1];
            memcpy(str_num, buffer, TAM_MSG);
            str_num[TAM_MSG] = '\0';
            long long n = strtoll(str_num, NULL, 10);
            if (n == 0)
                break;
            printf("N=%lld -> %s\n", n, eh_primo((uint64_t)n) ? "primo" : "nao_primo");
            fflush(stdout);
        }
        close(descritores[0]);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        close(descritores[0]);
        unsigned int semente = (unsigned int)(time(NULL) ^ getpid());
        long long N = 1;
        char mensagem[TAM_MSG + 1];

        for (long i = 0; i < quantidade; i++)
        {
            int delta = (rand_r(&semente) % 100) + 1;
            N += delta;
            memset(mensagem, ' ', TAM_MSG);
            int comprimento = snprintf(NULL, 0, "%lld", N);
            if (comprimento > TAM_MSG)
            {
                fprintf(stderr, "Numero %lld excede TAM_MSG=%d\n", N, TAM_MSG);
                close(descritores[1]);
                waitpid(pid, NULL, 0);
                return EXIT_FAILURE;
            }
            snprintf(mensagem + (TAM_MSG - comprimento), (size_t)comprimento + 1, "%lld", N);
            if (escrever_tudo(descritores[1], mensagem, TAM_MSG) < 0)
                abortar("write");
        }
        memset(mensagem, ' ', TAM_MSG);
        const char *zero = "0";
        memcpy(mensagem + (TAM_MSG - 1), zero, 1);
        if (escrever_tudo(descritores[1], mensagem, TAM_MSG) < 0)
            abortar("write_zero");

        close(descritores[1]);
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return EXIT_FAILURE;
        }
    }
}
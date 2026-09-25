#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s N\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    if (N <= 0) {
        printf("O tamanho da matriz deve ser positivo.\n");
        return 1;
    }

    double *A = malloc((size_t)N * N * sizeof(double));

    if (A == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
        }
    }

    struct timespec inicio, fim;
    long pares = 0;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec)
                 + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    printf("Varredura por linha\n");
    printf("N: %d\n", N);
    printf("Quantidade de pares: %ld\n", pares);
    printf("Tempo: %.6f s\n", tempo);

    free(A);
    return 0;
}
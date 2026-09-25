#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double tempo_segundos(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec)
         + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s N tamanho_bloco\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int bloco = atoi(argv[2]);

    if (N <= 0 || bloco <= 0) {
        printf("N e tamanho_bloco devem ser positivos.\n");
        return 1;
    }

    size_t quantidade = (size_t)N * N;

    double *A = malloc(quantidade * sizeof(double));
    double *B = malloc(quantidade * sizeof(double));
    double *C = calloc(quantidade, sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int ii = 0; ii < N; ii += bloco) {
        for (int jj = 0; jj < N; jj += bloco) {
            for (int kk = 0; kk < N; kk += bloco) {

                for (int i = ii; i < ii + bloco && i < N; i++) {
                    for (int k = kk; k < kk + bloco && k < N; k++) {
                        double r = A[i * N + k];

                        for (int j = jj; j < jj + bloco && j < N; j++) {
                            C[i * N + j] += r * B[k * N + j];
                        }
                    }
                }

            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = tempo_segundos(inicio, fim);
    double operacoes = 2.0 * N * N * N;
    double gflops = operacoes / (tempo * 1000000000.0);

    printf("Multiplicacao com blocagem\n");
    printf("N: %d\n", N);
    printf("Tamanho do bloco: %d\n", bloco);
    printf("Tempo: %.6f s\n", tempo);
    printf("GFLOPS: %.6f\n", gflops);
    printf("C[0][0]: %.2f\n", C[0]);
    printf("C[N-1][N-1]: %.2f\n", C[(N - 1) * N + (N - 1)]);

    free(A);
    free(B);
    free(C);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int N;
    int inicio;
    int fim;
    double *A;
    double *B;
    double *C;
} DadosThread;

double tempo_segundos(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec)
         + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
}

void *multiplicar(void *argumento) {
    DadosThread *dados = (DadosThread *)argumento;
    int N = dados->N;

    for (int i = dados->inicio; i < dados->fim; i++) {
        for (int j = 0; j < N; j++) {
            double soma = 0.0;

            for (int k = 0; k < N; k++) {
                soma += dados->A[i * N + k] * dados->B[k * N + j];
            }

            dados->C[i * N + j] = soma;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s N threads\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int T = atoi(argv[2]);

    if (N <= 0 || T <= 0 || T > N) {
        printf("Erro: N deve ser positivo e threads deve estar entre 1 e N.\n");
        return 1;
    }

    size_t total = (size_t)N * N;

    double *A = malloc(total * sizeof(double));
    double *B = malloc(total * sizeof(double));
    double *C = calloc(total, sizeof(double));

    pthread_t *threads = malloc((size_t)T * sizeof(pthread_t));
    DadosThread *dados = malloc((size_t)T * sizeof(DadosThread));

    if (A == NULL || B == NULL || C == NULL ||
        threads == NULL || dados == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(A);
        free(B);
        free(C);
        free(threads);
        free(dados);
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

    int criadas = 0;

    for (int t = 0; t < T; t++) {
        dados[t].N = N;
        dados[t].inicio = t * N / T;
        dados[t].fim = (t + 1) * N / T;
        dados[t].A = A;
        dados[t].B = B;
        dados[t].C = C;

        if (pthread_create(&threads[t], NULL, multiplicar, &dados[t]) != 0) {
            printf("Erro ao criar thread %d.\n", t);
            break;
        }

        criadas++;
    }

    for (int t = 0; t < criadas; t++) {
        pthread_join(threads[t], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);

    if (criadas != T) {
        free(A);
        free(B);
        free(C);
        free(threads);
        free(dados);
        return 1;
    }

    double tempo = tempo_segundos(inicio, fim);
    double operacoes = 2.0 * N * N * N;

    printf("Multiplicacao com Pthreads\n");
    printf("N: %d\n", N);
    printf("Threads: %d\n", T);
    printf("Tempo: %.6f s\n", tempo);
    printf("GFLOPS: %.6f\n", operacoes / tempo / 1000000000.0);
    printf("C[0][0]: %.2f\n", C[0]);
    printf("C[N-1][N-1]: %.2f\n", C[total - 1]);

    free(A);
    free(B);
    free(C);
    free(threads);
    free(dados);

    return 0;
}
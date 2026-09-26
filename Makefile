CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread

all: varredura_linha varredura_coluna matmul_padrao_O0 matmul_padrao_O3 matmul_bloco_O0 matmul_bloco_O3 matmul_pthreads matmul_pthreads_bloco

varredura_linha: varredura_linha.c
	$(CC) -O3 $(CFLAGS) varredura_linha.c -o varredura_linha

varredura_coluna: varredura_coluna.c
	$(CC) -O3 $(CFLAGS) varredura_coluna.c -o varredura_coluna

matmul_padrao_O0: matmul_padrao.c
	$(CC) -O0 $(CFLAGS) matmul_padrao.c -o matmul_padrao_O0

matmul_padrao_O3: matmul_padrao.c
	$(CC) -O3 $(CFLAGS) matmul_padrao.c -o matmul_padrao_O3

matmul_bloco_O0: matmul_bloco.c
	$(CC) -O0 $(CFLAGS) matmul_bloco.c -o matmul_bloco_O0

matmul_bloco_O3: matmul_bloco.c
	$(CC) -O3 $(CFLAGS) matmul_bloco.c -o matmul_bloco_O3

matmul_pthreads: matmul_pthreads.c
	$(CC) -O3 $(CFLAGS) $(PTHREAD) matmul_pthreads.c -o matmul_pthreads

matmul_pthreads_bloco: matmul_pthreads_bloco.c
	$(CC) -O3 $(CFLAGS) $(PTHREAD) matmul_pthreads_bloco.c -o matmul_pthreads_bloco

clean:
	rm -f varredura_linha varredura_coluna matmul_padrao_O0 matmul_padrao_O3 matmul_bloco_O0 matmul_bloco_O3 matmul_pthreads matmul_pthreads_bloco
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_MAX_MINE 11

typedef struct Ocorr {
    int line;
    int n_ocorr;
} Ocorr;

// SEPARAR EM VÁRIAS FUNÇÕES
// void lookupNumber(int** matrix, int rows, int target, int* result) Guarda o valor em result, vetor pre alocado
// int** gentMatrix(int rows, int cols)

int** genMatrix(int rows, int cols) {
    int** matrix = malloc(sizeof(int*) * rows);

    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % RAND_MAX_MINE;
        }
    }

    return matrix;
}

void printMatrix(int ** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv) {
    
    if (argc != 2) 
        perror("Número de argumentos incorreto\n");

    pid_t pid;
    int needle = atoi(argv[1]);
    int rows = 10;
    int cols = 10000; // Já conseguimos ao usar pipes
    int status, fork_ret, cont;
    int fd[2];
    int **matrix;

    // seed random numbers
    srand(time(NULL));

    matrix = genMatrix(rows, cols);
    //printMatrix(matrix, rows, cols);    

    if (pipe(fd) == -1)
        perror("Erro ao criar o pipe\n");

    for (int i=0; i < rows; i++) {
        fork_ret = fork();
        if (fork_ret == 0) {
            close(fd[0]);
            
            Ocorr o;
            o.line = i;
            o.n_ocorr = 0;

            for (int j=0; j < cols; j++) {
                if (matrix[i][j] == needle) {
                    printf("[child-%d] Found value at row %d\n", getpid(), i);
                    o.n_ocorr++;
                }
            }

            printf("[child-%d] Terminated, found %d", getpid(), o.n_ocorr);

            if (write(fd[1], &o, sizeof(Ocorr)) == -1) 
                perror("Erro a escrever no pipe\n");

            close(fd[1]);
            
            _exit(0);
        }
    }

    close(fd[1]);

    Ocorr o;
    int *res = malloc(sizeof(int) * rows);

    // Podiamos esperar que os filhos terminassem neste caso, porque o pipe buffer não enchia mas ter cuidado com isso
    // Preferível ler primeiro e só depois esperar que os filhos terminem
    while (read(fd[0], &o, sizeof(Ocorr)) > 0) {
        res[o.line] = o.n_ocorr;
    }

    close(fd[0]);

    for (int i = 0; i < rows; i++) {
        int status;
        wait(&status);
        if (!WIFEXITED(status))
            perror("Filho não terminou\n");
    }

    printf("Needle: %d\n", needle);

    for (int i = 0; i < rows; i++)
        printf("Line: %d, Ocorrences: %d\n", i, res[i]);


    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
    free(res);
    
    return 0;
}
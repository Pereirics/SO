#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// EXERCÍCIO 5 E 6

int main(int argc, char **argv) {

    pid_t pid;
    int needle = atoi(argv[1]);
    int rows = 10;
    int cols = 254; //10000; Para já não conseguimos 
    int rand_max = 1000;
    int status;
    int **matrix;

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numebers
    printf("Generating numbers from 0 to %d... ", rand_max);
    matrix = (int **) malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * cols);
        for (int j = 00; j < cols; j++) {
            matrix[i][j] = rand() % rand_max;
        }
    }
    printf("Done.\n");
 
    for (int i = 0; i < rows; i++) {
        if ((pid = fork()) == 0) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == needle) {
                    //printf("%d %d\n", i, j); Mostrar linha e coluna que a needle aparece
                    _exit(i); 
                    }
            }
            _exit(255); // Não encontrou na linha
        }
        else {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 255) {
                char exit_status_str[4];
                int length = snprintf(exit_status_str, 4, "%d\n", WEXITSTATUS(status));
                write(1, exit_status_str, length);
            }
        }
    }

    return 0;
}
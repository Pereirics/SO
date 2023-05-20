#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
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
    int pids[rows];
    int fd;

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numebers
    printf("Generating numbers from 0 to %d... ", rand_max);
    matrix = (int **) malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % rand_max;
        }
    }
    printf("Done.\n");


    // print matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j];
        }
    }
 
    for (int i = 0; i < rows; i++) {
        if ((pid = fork()) == 0) {
            printf("[pid %d] row: %d\n", getpid(), i);

            open();
            lseek();

            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == needle) {
                    //printf("%d %d\n", i, j); Mostrar linha e coluna que a needle aparece
                    _exit(i); // Encontrou na linha
                    }
                read();
            }
            _exit(-1); // Não encontrou na linha
        }
        else 
            pids[i] = pid;
    }

    for (int i = 0; i < rows; i++) {
        pid_t terminated_pid = waitpid(pids[i], &status, 0);

        if (WEXITSTATUS(status) < 255) {
            if (WEXITSTATUS(status) < 255)
                printf("[pai] process %d exited. found number at row: %d\n", terminated_pid, WEXITSTATUS(status));
            else 
                printf("[pai] process %d exited. nothing found\n", terminated_pid);
        } else {
            printf("[pai] process %d exited. something went wrong\n", terminated_pid);
        }
    }

    return 0;
}
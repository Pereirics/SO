#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char** argv) {

    int pid[argc];
    int status, return_value;

    for (int i = 1; i < argc; i++) {
        if ((pid[i] = fork()) == 0) {
            printf("Sou o filho %d e vou executar o %s\n", getpid(), argv[i]);
            
            return_value = execlp(argv[i], argv[i], NULL);

            perror("reached return");
            _exit(return_value);
        }
    }

    for (int i = 1; i < argc; i++) { // Começar no primeiro argumento e não executar o NULL
        printf("Sou o pai e estou à espera dos filhos terminarem\n");
        
        pid_t terminated_pid = waitpid(pid[i-1], &status, 0); // i-1 para começar na posição 0 do array
        
        printf("O filho com pid %d retornou %d\n", terminated_pid, WEXITSTATUS(status)); // i-1 pela mesma razão de cima
    }

    printf("Todos os filhos executaram\n");

    return 0;
}
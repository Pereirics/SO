#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(int argc, char **argv) {
    
    int i, status, pid;

    for (i=1; i<=10; i++) {
        if ((pid = fork()) == 0) { // fork retorna 0 ao processo-filho e o PID do filho ao processo-pai
            // Código processo-filho
            printf("Filho: %d Pai: %d\n", getpid(), getppid());
            _exit(i);
        }
        else {
            // Código processo-pai
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) 
                printf("Filho return value %d\n\n", WEXITSTATUS(status));
        }
    }        
    return 0;                                              
}

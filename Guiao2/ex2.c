#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(int argc, int **argv) {
    
    pid_t pid, ppid;
    if ((pid = fork()) == 0) { // fork retorna 0 ao processo-filho e o PID do filho ao processo-pai
        // Código processo-filho
        printf("Filho\nProcesso: %d, Processo pai: %d\n", getpid(), getppid());
    }
    else {
        // Código processo-pai
        printf("Pai\nProcesso: %d, Processo pai: %d, Processo filho %d\n", getpid(), getppid(), pid);
    }
    return 0;
}
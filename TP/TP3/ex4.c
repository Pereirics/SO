#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(int argc, char **argv) {
    
    int i, status, val[10];
    pid_t pid, pid_terminado, ppid = getpid();

    printf("Pai: %d\n", ppid);

    // Criação dos 10 processos filhos
    for (i=1; i<=10; i++) {
        if ((pid = fork()) == 0) {
            // Código processo-filho
            printf("Filho: %d Código saída: %d\n", getpid(), i);
            _exit(i);
        } 
    }

    // Esperar que os processos filhos terminem
    sleep(1);
    for (i=1; i<=10; i++) {
        pid_terminado = wait(&status);
        if (WIFEXITED(status)) 
            printf("Return value: %d\n", WEXITSTATUS(status));
        else {
            printf("Processo %d, sem valor de retorno", pid);
        }
    }


    return 0;
}
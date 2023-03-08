#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(int argc, int **argv) {
    
    int i, status, pid;

    for (i=1; i<=10; i++) {
        if ((pid = fork()) == 0) {
            // Código processo-filho
            printf("Filho: %d\n", getpid());
            sleep(1);
            _exit(i);
        } else {
            waitpid(getpid() + 10, &status, 1);
            printf("%d", WEXITSTATUS(status));
        }
    }

    return 0;
}
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(int argc, int **argv) {
    
    pid_t pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("%d %d", pid, ppid);
    
    return 0;
}
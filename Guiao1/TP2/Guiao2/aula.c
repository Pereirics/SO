#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <sys/wait.h>

int main() {

    int i=10;
    int status;
    pid_t my_pid = getpid();
    printf("my pid = %d\n", my_pid);

    pid_t parent_pid = getppid();
    printf("parent pid = %d\n", parent_pid);

    pid_t res = fork();

    if (res == 0) {
        i = i-5;
        printf("filho | pid = %d\n", getpid());
        printf("filho | parent pid = %d\n", getpid());
        printf("filho | i = %d\n", i);
        _exit(0);
    } else {
        i = i+5;
        printf("pai | pid = %d\n", getpid());
        printf("pai | parent pid = %d\n", getpid());
        printf("pai | filho pid = %d\n", res);
        printf("pai | i = %d\n", i);
        pid_t filho_terminou = wait(&status);
        printf("pai | depois do wait\n");
        printf("pai | filho terminou = %d\n", filho_terminou);
        if (WIFEXITED(status)) {
            printf("filho return value: %d\n", WEXITSTATUS(status));
        } else {
            printf("processo filho falhou");
        }
       
    }

    printf("pid=%d vou terminar\n", getpid());

    return 0;
}
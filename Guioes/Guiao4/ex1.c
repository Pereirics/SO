#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

void pai_to_filho() {

    int fd[2], res = 0, status;
    __pid_t pid;

    if (pipe(fd) == -1) 
        perror("Erro ao criar o pipe\n");

    printf("fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);

    if ((pid = fork()) == 0) {
        close(fd[1]);

        if (read(fd[0], &res, sizeof(int)) == -1) 
            perror("FILHO | Erro ao ler do pipe\n");
        printf("FILHO | Li o valor %d\n", res);

        close (fd[0]);
        _exit(0);
    }
    else {
        int value = 1024;
        close(fd[0]);
        
        printf("PAI | Vou enviar o valor %d\n", value);
        if (write(fd[1], &value, sizeof(int)) == -1)
            perror("PAI | Erro ao escrever para o pipe\n");
        
        close(fd[1]);
        wait(&status);
    }

}


int main(int argc, char** argv) {

    pai_to_filho();

    return 0;
}
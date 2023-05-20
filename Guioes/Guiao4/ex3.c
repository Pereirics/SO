#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

void filho_to_pai() {

    int fork_ret, status, res, fd[2];

    if (pipe(fd) == -1) 
        perror("Erro ao criar o pipe\n");

    fork_ret = fork();
    if (fork_ret == 0) {
        close(fd[0]);

        int value = 1024;
        printf("FILHO | Vou enviar o valor %d\n", value);

        if (write(fd[1], &value, sizeof(int)) == -1) 
            perror("FILHO | Erro ao enviar o valor para o pipe\n");
        printf("FILHO | Enviei o valor %d", value);

        close(fd[1]);
        _exit(0);
    }
    else {
    
        close(fd[1]);

        printf("PAI | Vou ler o valor do pipe\n");

        if ((read(fd[0], &res, sizeof(int))) == -1)
            perror("PAI | Erro ao ler o valor do pipe\n");
        printf("PAI | Li o valor %d\n", res);

        close(fd[0]);

        wait(&status);

        if (WIFEXITED(status)) {
            printf("Processo FILHO terminou com sucesso\n");
        }
        else 
            printf("Processo FILHO não terminou corretamente\n");
    }

}


int main(int argc, char** argv) {

    filho_to_pai();

    return 0;
}
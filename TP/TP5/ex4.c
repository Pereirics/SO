#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void pai_to_filho() {

    int status;
    
    int p[2];
    if (pipe(p) == -1) {
        perror("erro ao criar o pipe\n");
    }

    printf("p[0] = %d, p[1] = %d\n", p[0], p[1]);

    int fork_ret = fork();
    if (fork_ret == 0) {
        int res = 0;
        close(p[1]);
        if (read(p[0], &res, sizeof(int)) == -1)
            perror("FILHO | erro ao ler do pipe\n");
        printf("FILHO | li o valor %d\n", res);
        close(p[0]);
        _exit(0);

    } else {
        int value = 940; // Já conseguimos enviar valores maiores que 254
        close(p[0]);
        printf("PAI | vou enviar o valor value %d\n", value);
        if (write(p[1], &value, sizeof(int)) == -1)
            perror("PAI | erro ao escrever para o pipe\n");
        close(p[1]);
        wait(&status);
    }

}

void filho_to_pai() {

    int status;
    
    int p[2];
    if (pipe(p) == -1) {
        perror("erro ao criar o pipe\n");
    }

    printf("p[0] = %d, p[1] = %d\n", p[0], p[1]);

    int fork_ret = fork();
    if (fork_ret == 0) {
        int value = 940; // Já conseguimos enviar valores maiores que 254
        close(p[0]);
        printf("FILHO | vou enviar o valor value %d\n", value);
        if (write(p[1], &value, sizeof(int)) == -1)
            perror("FILHO | erro ao escrever para o pipe\n");
        close(p[1]);
        wait(&status);

    } else {
        int res = 0;
        close(p[1]);
        sleep(10);
        if (read(p[0], &res, sizeof(int)) == -1)
            perror("PAI | erro ao ler do pipe\n");
        printf("PAI | li o valor %d\n", res);
        close(p[0]);
        _exit(0);
    }

}

int main(int argc, char* argv) {

    //pai_to_filho();
    filho_to_pai();

    return 0;
}
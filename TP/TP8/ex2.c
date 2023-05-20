#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    char buffer[100];
    int res;

    int f;
    int status;
    int fd_pass;
    int fd_saida;
    int fd_erros;

    fd_pass = open("/etc/passwd", O_RDONLY);
    fd_saida = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    fd_erros = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    //dup2(fd_pass, 0);
    //close(fd_pass);

    //dup2(fd_saida, 1);
    //close(fd_saida);

    //dup2(fd_erros, 2);
    //close(fd_erros);

    f = fork();
    if (f == 0) {
        printf("Sou o filho e tenho PID:%d", getpid());

        // Com dups dentro do filho, os fd do pai não são alterados
        // Quando são feitos no pai, os fd do filho ficam iguais ao do pai
        dup2(fd_pass, 0);
        close(fd_pass);

        dup2(fd_saida, 1);
        close(fd_saida);

        dup2(fd_erros, 2);
        close(fd_erros);

        while ((res=read(0, buffer, sizeof(buffer))) > 0) {
            write(1, buffer, res);
            write(2, buffer, res);
            printf("Ola\n");
            fflush(stdout);
        }
        _exit(0);
    }
    else {

        close(fd_pass);
        close(fd_saida);
        close(fd_erros);

        int wait_ret = wait(&status);
        if (WIFEXITED(status))
            printf("O filho retonou %d\n", wait_ret);
        else
            printf("O filho não terminou.\n");
    }

    printf("Terminei\n");   

    return 0;
}
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main (int argc, char** argv) {

    char buffer[100];
    int res;

    int fd_pass;
    int fd_saida;
    int fd_erros;
    int fd_in;
    int fd_out;
    int fd_error;

    fd_pass = open("/etc/passwd", O_RDONLY);
    fd_saida = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    fd_erros = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    fd_in = dup(0);
    fd_out = dup(1);
    fd_error = dup(2);

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
    
    dup2(fd_in, 0);
    close(fd_in);
    dup2(fd_out, 1);
    close(fd_out);
    dup2(fd_error, 2);
    close(fd_error);

    printf("Terminei\n");   

    return 0;
}
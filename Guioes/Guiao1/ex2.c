#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

#define MAX_SIZE 1024

// PASSOS
// 1- Verificar se tem argumentos (ficheiros a imprimir)
// 2- Se tiver ficheiro a imprimir
//     2.1 - Abrir o ficheiro
//     2.2 - Ler o ficheiro e escrever no stdout
// 3-  Se não tiver ficheiro a imprimir
//     3.1 - Ler do stdin até uma mudança de linha (\n)
//     3.2 - Escrever no stdout o conteúdo lido
//     3.3 - Continuar o 3.1 e 3.2 enquanto não for terminado (CTRL+D)


int mycat(int argc, char** argv) {

    int fd, bytes_read, bytes_written = 0, ret = 0;
    char buffer[MAX_SIZE];

    if (argc > 1) { // Se tiver ficheiros a imprimir
        for (int i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY); // Abrir o ficheiro
            if (fd == -1) 
                perror("Erro ao abrir o ficheiro");
            while ((bytes_read = read(fd, buffer, MAX_SIZE)) > 0) {
                bytes_written += write(1, buffer, bytes_read);
            }
            if (bytes_read == -1)
                perror("Erro ao ler do ficheiro");
            if (bytes_written == -1) 
                perror("Erro ao escrever para o stdout");
        }
    }
    else { // Se não tiver ficheiros a imprimir
        while ((bytes_read = read(0, buffer, MAX_SIZE)) > 0) { // Ler do stdin até um \n
            bytes_written = write(1, buffer, bytes_read); // Escrever no stdout o conteúdo lido
        }
        if (bytes_read == -1)
            perror("Erro ao ler do stdin");
        if (bytes_written == -1) 
            perror("Erro ao escrever para o stdout");
    }

    if (fd == -1) ret = -1;
    close(fd);

    return ret;
}

int main(int argc, char** argv) {

    int ret;

    if (argc > 0) {
        ret = mycat(argc, argv);
    }
    else perror("Erro no número de argumentos.");

    if (ret == -1) 
        perror("Erro na função mycat");

    return 0;

}
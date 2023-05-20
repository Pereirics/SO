#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

#define MAX_SIZE 1024

// Passos
// 1- Ler os argumentos dados (ficheiro source e ficheiro destino)
// 2- Abrir o ficheiro source
// 3- Abrir/Criar o ficheiro de destino
// 4- Ler o ficheiro source
// 5- Escrever o conteúdo lido do ficheiro source no ficheiro destino
// 6- Fechar

int mycp(char* source, char* dest) {

    int fd_s, fd_d;
    int bytes_read = 0, bytes_written = 0;
    char buffer[sizeof(source)];

    printf("%s %s\n", source, dest);
    if ((fd_s = open(source, O_RDONLY)) == -1) // Abrir o ficheiro source
        perror("Error opening the source file");
    if ((fd_d = open(dest, O_WRONLY| O_CREAT | O_TRUNC, 0666)) == -1) // Abrir/Criar o ficheiro destino
        perror("Error opening/creating the destination file");

    while ((bytes_read = read(fd_s, buffer, sizeof(buffer))) > 0) { // Ler o ficheiro source
        bytes_written += write(fd_d, buffer, bytes_read); // Escrever o conteúdo lido do ficheiro source no ficheiro destino
    }



    close(fd_s);
    close(fd_d);

    return bytes_written;
}


int main(int argc, char** argv) {

    int bytes_written = 0;

    if (argc == 3) {
        bytes_written = mycp(argv[1], argv[2]); // Ler os argumentos dados
    }

    printf("Bytes written: %d", bytes_written);

    return 0;

}
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

// Abre ficheiro no caminho de argv[1] (fonte)
// Ler conteúdo do ficheiro argv[1], guardando-o num buffer
// Abrir o ficheiro no caminho argv[2] (destino)
// Se o ficheiro 2 não existe, cria
// Escrever o conteúdo do buffer no ficheiro 2
// Fechar os ficheiros


// fd é file descriptor, diz para onde apontar no array

int main (int argc, char**argv) {
    int fd_1, fd_2, bytes_read;
    char buffer[1024];
    if ((fd_1 == open(argv[1], O_RDONLY)) == -1) return -1;
    fd_2 = open(argv[2], O_WRONLY|O_CREAT, 7777);
    while ((bytes_read = read(fd_1, buffer, 1024)) != 0) 
        write(fd_2, buffer, bytes_read);
    close(fd_1);
    close(fd_2);
    return 0;
}



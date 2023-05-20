#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Como por o servidor a nunca parar

int main (int argc, char** argv) {

    int res, bytes_read, fd, fd1, buffer[4096];

    res = mkfifo("servidor", 0666);
    if (res == -1) 
        perror("Erro ao criar o fifo");

    fd = open("servidor", O_RDONLY);
    if (fd == -1) 
        perror("Erro ao abrir o fifo");

    fd1 = open("servidor", O_WRONLY); // Mantém o servidor a correr

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
        write(1, buffer, bytes_read);

    close(fd);
    close(fd1);
    unlink("servidor");

    return 0;
}
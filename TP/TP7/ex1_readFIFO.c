#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Mostrar criação fifo e erro caso eista

int main (int argc, char** argv) {

    char buffer[4096];
    int bytes_read;

    int fd = open("fifo", O_RDONLY);    

    printf("Abri o fifo escritor\n");

    while ((bytes_read = read(fd, buffer, sizeof(buffer)))> 0) {
        write(1, buffer, bytes_read);
    }

    printf("Saí do while descritor");

    close(fd);
    unlink("fifo");

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// Versão minha e do Tiago
/*
ssize_t readln(int fd, char *line, size_t size) {

    ssize_t bytes_read = 0;
    char* lines = malloc(size);
    strncpy(lines, line, size);

    while (!strcmp(*lines, "\n")) {
        read(fd, buffer, 1);
        lines++;
        bytes_read++;
    }
    return bytes_read;
}
*/

// Versão professor
ssize_t readln(int fd, char *line, size_t size) {
    
    int pos = 0;
    int bytes_read = 0;

    while (pos < size && read(fd, line + pos, 1) > 0) { //Posição é menor que o tamanho do buffer e ainda não acabou
        bytes_read++;
        if (line[pos] == '\n') break;
        pos++;
    }

    return bytes_read;
}




int main (int argc, char** argv){ 

    // Buffer já está criado e o char* já está inicializado
    char* buffer = malloc(sizeof(char)*1024);
    int bytes_read = 0;
    int bytes_written = 0;

    int fd_in = open("tmp.txt", O_RDONLY);

   

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char** argv){

    char* buffer = malloc(sizeof(char)*1024);
    int bytes_read = 0;
    int bytes_written = 0;

    int fd_in = open("tmp.txt", O_RDONLY);
    int fd_out = open("tmp.txt.bak", O_WRONLY, 0644);    

    while ((bytes_read = read(fd_in, buffer, 1024)) > 0) { //0 é stdin
        bytes_written += write(1, buffer, bytes_read); // 1 é stdout
    }

    printf("> %d == %s\n", bytes_written, buffer);
    return 0;
}
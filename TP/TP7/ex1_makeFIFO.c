#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Mostrar criação fifo e erro caso eista

int main (int argc, char** argv) {
    int res = mkfifo("fifo", 0666);
    if (res == -1)
                perror("Erro na função a");
       
    return 0;
}
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char** argv) {

    int fd = open("servidor", O_WRONLY);

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}


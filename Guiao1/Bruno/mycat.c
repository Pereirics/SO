#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main (int argc, char**argv) { //argc vai ser o número de argumentos
    int bytes_read, buffer[1024], i=1, fd;
    if (argc == 1) {
        while ((bytes_read = read(0, buffer, 1024)))
            write(1, buffer, bytes_read);
    }
    else {
    while (i < argc) {
        if ((fd = open(argv[i], O_RDONLY)) == -1) return -1;
        while ((bytes_read = read(fd, buffer, 1024)))
            write(1, buffer, bytes_read);
        close(fd);
        i++;
    }
    }
    return 0;
}

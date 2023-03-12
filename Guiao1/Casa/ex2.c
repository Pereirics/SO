#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h> /* perror */

// TO-DO: ATUALIZAR PERROR PARA WRITE(2,...,...)

int main(int argc, char** argv) {

    int fd, bytes_read, bytes_written, buffer[1024], i = 1, flag = 0;

    if (argc == 1) {// Só o nome do ficheiro
        while((bytes_read = read(0, buffer, sizeof(buffer))) != -1) {
            bytes_written = write(1, buffer, bytes_read);
        }
        if (bytes_read == -1) {
            flag = 1;
            perror("error reading from stdin");
        }
    }
    else {
        while(!flag && i < argc) {
            if ((fd = open(argv[i], O_RDONLY, 0600)) == -1) {
                flag = 1;
                perror("error reading input file");
            }
            else {
                while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) 
                    bytes_written = write(1, buffer, bytes_read);
                if (bytes_read == -1) {
                    perror("error reading input file");
                    flag = 1;
                }
                else if (bytes_written == -1) {
                    perror("error writing stdout");
                }
                close(fd);
                i++;
            }
        }
    }

    if (flag) return -1;
    return 0;
}
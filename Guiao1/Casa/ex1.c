#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h> /* perror */

// TO-DO: ATUALIZAR PERROR PARA WRITE(2,...,...)

int main(int argc, char** argv) {

    int buffer[1024];
    int fd1, fd2, bytes_read, bytes_written, flag = 0;

    if ((fd1 = open(argv[1], O_RDONLY, 0600)) == -1) {
        perror("open input file");
        flag = 1;
    }
    
    if (!flag && (fd2 = open(argv[2], O_TRUNC | O_WRONLY|O_CREAT, 0600)) == -1) {
        perror("open output file");
        flag = 1;
        close(fd1);
    }

    while(!flag && ((bytes_read = read(fd1, buffer, sizeof(buffer))) > 0)) {
        bytes_written = write(fd2, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("write output file");
            flag = 1;        
        }
    }

    if (bytes_read == -1){
        perror("read input file");
        flag = 1;
    }

    close(fd1);
    close(fd2);

    if (flag) return -1;
    
    return 0;
}
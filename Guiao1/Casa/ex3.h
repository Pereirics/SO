#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h> /* perror */

ssize_t readln(int fd, char* line, size_t size) {
    
    int bytes_read = 0, next_pos = 0;
    
    while (next_pos < size && (read(fd, line + next_pos, 1) > 0)) {
        bytes_read++;
        
        if (line[next_pos] == '\n') break;

        next_pos++;
    }

    return bytes_read;
}
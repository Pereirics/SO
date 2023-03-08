#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

ssize_t readln(int fd, char* line, size_t size) {
    int next_pos = 0;
    int read_bytes = 0;

    while (next_pos < size && read(fd, line + next_pos, 1) > 0) {
        read_bytes++;

        if (line[next_pos] == '\n') {
            break;
        }

        next_pos++;
    }

    return read_bytes;
}
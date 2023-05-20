#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h> /* perror */
#include "ex3.h"

#define MAX_SIZE 100000

int main(int agrc, char** argv) {

    int fd, bytes_read, i = 1;
    char buffer[MAX_SIZE];

    while ((bytes_read = readln(0, buffer, sizeof(buffer))) > 0) {
        char line_str[bytes_read + 10];
        int length = snprintf(line_str, sizeof(line_str), "      %d: %s", i, buffer);
        write(1, line_str, length);
        if (buffer[bytes_read-1] != '\n') write(1, "\n", 1);
        i++;
    }

    return 0;
}
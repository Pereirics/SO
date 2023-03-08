#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_BUFFER 10

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

 int main (int argc, char *argv[]){

    int line_counter = 0;
    char buffer[MAX_BUFFER];
    int bytes_read = 0;
    int new_line = 1;

    while ((bytes_read = readln(0, buffer, MAX_BUFFER)) > 0) {
        char line_number[cont] = "";
        snprintf(line_number, cont, "%d:", line_counter);
        write(1, line_number, sizeof(line_number));
        line_counter++;
        write(1, buffer, bytes_read);
        
        if () new_line = 1;
        else new_line = 0;    
    }

    return 0;
 }
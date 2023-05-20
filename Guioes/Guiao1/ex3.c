#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

ssize_t readln(int fd, char *line, size_t size) {
	
    ssize_t i = 0;

	while(read(fd, &line[i], 1) && line[i++] != '\n');

	return i;
}

int main(int argc, char** argv) {

    int fd = open(argv[1], O_RDONLY, 0666);
    char* line;
    size_t size = 100;

    readln(fd, line, size);

    return 0;
}
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    char buffer[100];
    int res;
    int p[2];
    int status;

    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        dup2(p[0], 0);
        close(p[0]);
        execlp("wc", "wc", "-l", NULL);
    }
    else {
        close(p[0]);
        int bytes_read;
        
        dup2(p[1], 1);
        close(p[1]);
        execlp("ls", "ls", "/etc", NULL);
    }

    return 0;
}
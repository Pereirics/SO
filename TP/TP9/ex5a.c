#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    char buffer[100];
    int res;
    int p[2];
    int status[2];
    
    pipe(p);

    if (fork() == 0) {
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);
        execlp("ls", "ls", "/etc", NULL);
    }

    close(p[1]);

    if(fork() == 0) {
        dup2(p[0], 0);
        close(p[0]);
        execlp("wc", "wc", "-l", NULL);
    }

    close(p[0]);

    for(int i=0; i<2; i++) {
        wait(&status[i]);
        if (WIFEXITED(status[i]))
            printf("[PAI]: o processo filho terminou com %d\n", WEXITSTATUS(status[i]));
    }
        
    return 0;
}
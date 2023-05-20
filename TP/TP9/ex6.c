#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    char buffer[100];
    int res;
    int status[4];
    int p[2], p1[2], p2[2];
    
    pipe(p);

    if(fork() == 0) {
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);
        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
    }
    
    close(p[1]);
    pipe(p1);
    
    if (fork() == 0) {
        close(p1[0]);
        
        dup2(p[0], 0);
        close(p[0]);

        dup2(p1[1], 1);
        close(p1[1]);
        
        execlp("cut", "cut", "-f7", "-d:", NULL);
    }

    close(p1[1]);
    close(p[0]);
    pipe(p2);

    if (fork() == 0) {
        close(p2[0]);

        dup2(p1[0], 0);
        close(p1[0]);

        dup2(p2[1], 1);
        close(p2[1]);

        execlp("uniq", "uniq", NULL);
    }

    close(p2[1]);
    close(p1[0]);

    if (fork() == 0) {        
        dup2(p2[0], 0);
        close(p2[0]);

        execlp("wc", "wc", "-l", NULL);
    }
        
    close(p2[0]);

    for(int i=0; i<4; i++) {
        wait(&status[i]);
        if (WIFEXITED(status[i]))
            printf("[PAI]: o processo filho terminou com %d\n", WEXITSTATUS(status[i]));
    }

    return 0;
}
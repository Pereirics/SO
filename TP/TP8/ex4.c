#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

// Posso usar um switch em vez de if-then-else

int main (int argc, char** argv) {

    char buffer[100];
    int res;
    int p[2];
    int status;

    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        dup2(p[0], 0);
        execlp("wc", "wc", NULL);
        close(p[0]);
    }
    else {
        close(p[0]);
        int bytes_read;
        while(bytes_read=read(0, buffer, sizeof(buffer))) {
            write(p[1], buffer, bytes_read);
        }
        close(p[1]);

        wait(&status);
        if(WIFEXITED(status))
            printf("[PAI] Filho terminou com %d\n", WEXITSTATUS(status));
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <string.h>

// PASSOS
// 1- Usar strstep para separar a string em argv
// 2- O pai vai ter que esperar que o filho termine e devolve o valor de retorno do filho da função

int mysystem(char* comando) {

    int ret = -1;
    int pid, status, i = 0;

    char* argv[10];
    char* cmd = strdup(comando);
    char* token = NULL;
    token = strsep(&cmd, " ");
    

    while (token != NULL) {
        argv[i] = token;
        //printf("%s\n", argv[i]);
        token = strsep(&cmd, " ");
        i++;
    }

    argv[i] = NULL;

    if ((pid=fork()) == 0) {
        ret = execvp(argv[0], argv);
        _exit(-1);
    }
    else if (pid == -1) ret = -1;
    else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) 
            ret = WEXITSTATUS(status);
        else ret = -1;
    }

    free(cmd);

    return ret;
}

int main(int argc, char**argv) {

    char comando1[] = "ls -l -a -h";
    char comando2[] = "sleep 10";
    char comando3[] = "ps";

    int ret;

    printf("A executar mysystem para %s\n", comando1);
    ret = mysystem(comando1);
    printf("ret: %d\n", ret);
    
    printf("A executar mysystem para %s\n", comando2);
    ret = mysystem(comando2);
    printf("ret: %d\n", ret);

    printf("A executar mysystem para %s\n", comando3);
    ret = mysystem(comando3);
    printf("ret: %d\n", ret);
    

    printf("Todos os comandos executaram.\n");

    return 0;
}
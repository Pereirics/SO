#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <string.h>

#define MAX_SIZE 1000

// Parar com o CTRL+D e ao utilizador escrever exit 

void ler(int argc, char* argv) {

    int bytes_read, size;
    char* buffer;

    while ((bytes_read=read(0, buffer, 0600)) > 0) 
        size += bytes_read;

    
    

}

int main(int argc, char* argv) {


}
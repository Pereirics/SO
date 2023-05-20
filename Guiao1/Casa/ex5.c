#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h> /* perror */
#include <string.h>
#include <stdlib.h>

typedef struct Pessoa{
    char name[200];
    int age;
} Person;

void add_pessoa(char* nome, int idade) {

    Person nova;

    int res, flag = 0, fd = open("dados.txt", O_CREAT | O_RDWR | O_APPEND, 0600);
    strncpy(nova.name, nome, sizeof nome);
    nova.age = idade;

    lseek(fd, 0, SEEK_END);
    
    res = write(fd, &nova, sizeof(Person));
    if (res < 0) {
        perror("Error creating person");
        flag = 1;
    }
}


void update_idade(char* nome, int idade) {

}

int main(int argc, char** argv) {

    if (!strcmp(argv[1], "-i")) {
        add_pessoa(argv[2], atoi(argv[3]));
    }
    else if (!strcmp(argv[1], "-u")) {
        update_idade(argv[2], atoi(argv[3]));
    }


}
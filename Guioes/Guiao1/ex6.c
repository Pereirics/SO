#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// PASSOS
// 1- Verificar os argumentos para escolher a função a executar
// 2- Função para adicionar pessoa 
//     2.1 - Abrir/Criar o ficheiro
//     2.2 - Adicionar a pessoa (Flag O_APPEND)
// 3- Função para atualizar pessoa
//     3.1 - Abrir o ficheiro
//     3.2 - Procurar pelo nome da pessoa no ficheiro (lseek)
//     3.3 - Atualizar o valor da idade para essa pessoa

typedef struct Pessoas{
    int   age;
    char name[200];
} Pessoas;

void add_pessoas(int age, char* name) {

    int fd;

    Pessoas p;
    p.age = age;
    strcpy(p.name, name);

    if ((fd = open("dados.txt", O_RDWR | O_APPEND | O_CREAT, 0666)) == -1) 
        perror("Erro ao abrir/criar o ficheiro\n");

    if ((write(fd, &p, sizeof(Pessoas))) == -1) 
        perror("Erro ao escrever para o ficheiro\n");

    int seek_res = lseek(fd, -sizeof(Pessoas), SEEK_CUR);
    if (seek_res < 0) 
        perror("Erro lseek");

    printf("Registo %ld", seek_res/sizeof(Pessoas));

    close(fd);
}

void update_pessoas(long pos, int age) {

    int fd = open("dados.txt", O_WRONLY, 0666);
    int seek_res = lseek(fd, pos*sizeof(Pessoas), 0600);

    close(fd);
}

int main(int argc, char** argv){

    if (argc < 4)
        perror("Número de argumentos insuficiente\n");
    else if (argc > 4) 
        perror("Número de argumentos excessivo\n");
    else {
        if (!strcmp(argv[1], "-i")) 
            add_pessoas(atoi(argv[3]), argv[3]);
        else if (!strcmp(argv[1], "-o"))
            update_pessoas(atoi(argv[1]), atoi(argv[2]));
        else
            perror("Erro nos argumentos\n");
    }
    
    return 0;
}
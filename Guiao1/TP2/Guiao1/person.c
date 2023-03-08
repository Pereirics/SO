#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>
#include "person.h"

// PASSOS
// 1-Abrir o ficheiro (read)
// 2-Criar a pessoa 
// 3-Adicionar a pessoa ao ficheiro (write(fd, &p, sizeof pessoa))
// 4-Fechar

int new_person(char* name, int age) {
    int res, fd = open("teste", O_WRONLY|O_CREAT|O_APPEND, 0640);
    
    Person p;
    p.age = age;
    strncpy(p.name, name, sizeof name);

    res = write(fd, &p, sizeof(Person));
    if (res<0) {
        perror("Error creating person");
        return -1;
    }

    //Ex 7

    int seek_res = lseek(fd, -sizeof(Person), SEEK_CUR);
    if(seek_res<0){
        perror("Error lseek");
        return -1;
    }

    close(fd);

    return seek_res/sizeof(Person);
}

// PASSOS
// 1-Abrir o ficheiro (read)
// 2-Usar o lseek para procurar a pessoa
// 3-Se encontrar voltanmos o tamanho de uma pessoa
// 4-Escrever a idade atualizada nessa pessoa
// 5-Fechar

int person_change_age(char* name, int age) {
    int fd = open("teste", O_RDWR, 0640);
}

// No 6. ao adicionar uma pessoa retorna a posição em que é escrita
// Assim ao atualizarmos utilizamos a idade nessa posição (E o nome também por segurança)

int person_change_age_v2(long pos, int age) {

    int fd = open("teste", O_WRONLY, 0640);
    int seek_res = lseek(fd, pos*sizeof(Person), 0600);
}

int main(int argc, char**argv) {
    
    new_person("José Mourinho", 60);

    return 0;
}
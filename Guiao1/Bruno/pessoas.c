#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pessoa
{
    int idade;
    char nome[64];
};

/*
void inserir (char* str, char* age) {
    struct pessoa Pessoa;
    char buffer[64];
    int fd, file_size, curr, found;
    Pessoa.idade = atoi(age);
    strncpy(Pessoa.nome, str, 64);
    if ((fd = open("./dados.txt", O_RDWR|O_APPEND)) == -1) return;
    else {
        curr = lseek(fd, 0, SEEK_SET);
        file_size = lseek(fd, 0, SEEK_END);
        found = 0;
        while (curr < file_size && !found) {
            curr = lseek(fd, sizeof (int), SEEK_CUR); // Passa a idade à frente
            read(fd, buffer, sizeof(char)*64);
            if (!strcmp(Pessoa.nome, buffer)) found = 1;
            curr = lseek(fd, sizeof(char)*64, SEEK_CUR);
        }
        if (!found)
            write(fd, &Pessoa, sizeof Pessoa);
    }
    close(fd);
}
*/

int inserir(char*name, char*age){
  struct pessoa Person;
  int fd, flag_err = 1; off_t curr, max;
  int flag_cont = 1;
  char buffer[64];
  Person.idade = atoi(age);
  strncpy(Person.nome, name, 64);
  if ( (fd = open("./dados.txt", O_RDWR | O_APPEND) ) == -1) flag_err = 2;
  else
  { max = lseek(fd, 0, SEEK_END);
    curr = lseek(fd, 0, SEEK_SET);
    while (curr < max && flag_cont)
    { curr = lseek(fd, curr+sizeof (int), SEEK_CUR);
      read(fd, buffer, sizeof (char)*64);
      if (!strcmp(name, buffer)) flag_cont = 0;
      curr = lseek(fd, curr+sizeof (char)*64, SEEK_CUR);
    }
    if (flag_cont)
      write(fd, &Person, sizeof (struct pessoa));
    else flag_err = 3;
  }
  return flag_err;
}

void update(char* str, char* age) {
    int fd = open("./dados.txt", O_RDWR);

}

int main (int argc, char**argv) {
    
    if (argc != 4) return -1;
    if (!strcmp(argv[1], "-i"))
        inserir(argv[2], argv[3]);
    else if (!strcmp (argv[1], "-u"))
       update(argv[3], argv[4]);
    else return 1;
    
    return 0;
}


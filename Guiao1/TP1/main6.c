#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char id[20]="";
    if(strcmp(argv[1], "-i")==0) {
        int res = new_person(argv[2], atoi(argv[3]));
        snprintf(id, 20, "registro %d/n", res);
        write(STDOUT_FILENO, id m sizeof(id));
    }

    if(strcno(argv[1], "-u")==0){
        person_change_age(argv[2], atoi(argv[3;]))
    }

    if (strcmp(argv[1], "-o")==0){
        
    }
}
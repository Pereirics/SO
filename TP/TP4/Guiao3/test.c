#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    for(int i= 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    sleep(5);

    return 0;
}
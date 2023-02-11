#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    printf("%d\n", argc-1);
    for(int i=1; i<=argc-1; i++){
        printf("%s\n", argv[i]);
    }
    return 0;
}

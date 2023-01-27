#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv){
   
    void *handle;
    char *error, argvParUm;
    int  (*imprime)(void), (*calcula)(int, int), (*trigo)(double), charToIntUm, charToIntDois;
    double charToDouble;

    handle = dlopen(argv[1], RTLD_LAZY);
    error = dlerror();

    if (!handle || error != NULL) {
        printf("nao disponivel\n");
        return 0;
    }
    
    imprime = dlsym(handle, "imprime");
    error = dlerror();

    if (!imprime || error != NULL)  {
        printf("nao implementado\n"); 
    } else {
        printf("%d\n", imprime());
    }

    calcula = dlsym(handle, "calcula");
    error = dlerror();

    if (!calcula || error != NULL)  {
        printf("nao implementado\n");
    } else {
        charToIntUm = atoi(argv[2]);
        charToIntDois = atoi(argv[3]);
        printf("%d\n", calcula(charToIntUm, charToIntDois));
    } 

    trigo = dlsym(handle, "trigo");
    error = dlerror();

    if (!trigo || error != NULL)  {
        printf("nao implementado\n");
    } else {
        charToDouble = strtod(argv[4], NULL);
        printf("%d\n", trigo(charToDouble));
    }

    dlclose(handle);
    
    return 0;
}


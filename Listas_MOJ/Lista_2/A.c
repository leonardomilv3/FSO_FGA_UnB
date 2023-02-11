#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>


typedef struct {
    int index, tamanho, *v; 
} thread_arg, *ptr_thread_arg;

pthread_t threads[2];
thread_arg arguments[2];

int cmpfunc(const void * a, const void * b);
void* thread_func(void *arg);


int main(int argc, char const *argv[]){
    
    int i=0, tamanhoVetor, vetoresDiferentes = 0; 

    scanf("%d", &tamanhoVetor);

    arguments[0].v = malloc(sizeof(int)*(tamanhoVetor));
    arguments[1].v = malloc(sizeof(int)*(tamanhoVetor));

    for (int j=0, i=0; i<2; j++) {
        scanf("%d", &arguments[i].v[j]);
        /* printf("%d - %d\n", i, j); */
        if (j==tamanhoVetor-1){
            j=-1;
            i++;
        }
    }

    for (i=0; i<2; i++){
        arguments[i].index = i * 10;
        arguments[i].tamanho = tamanhoVetor;
        pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
    }

    for (i=0; i<2 ; i++) {
        pthread_join(threads[i], NULL);
    }

    for (i=0; i<tamanhoVetor ; i++) {
        if (arguments[0].v[i] != arguments[1].v[i]){
            vetoresDiferentes = 1;
            break;
        }
    }   

    if (!vetoresDiferentes) {
        printf("Mesmos elementos\n");
    } else {
        printf("Diferentes\n");
    }

    free(arguments[0].v);
    free(arguments[1].v);

    return 0;
}


void* thread_func(void *arg){

    ptr_thread_arg targ = (ptr_thread_arg)arg;

    int i; 

    qsort(targ->v, targ->tamanho, sizeof(int), cmpfunc);
    
}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

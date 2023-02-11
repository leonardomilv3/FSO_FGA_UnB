#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

teste_quasePrimo(int n) {
    if(n==1 || n%2==0)
        return 0;

    int count=0;

    for(int i=3,f=floor(sqrt(n));i<f;i+=2){
        if(n%i==0 && i<11)
            return 0;
        else if(n%i==0 && i>10)
            count++;
        else if(count>=10) 
            return 1;
    }

    return 0;
}


void *calcule_sequaseprimo_maluco(void *args) {
    int *prm = args;
    int n = *prm++;
    // printf("%d\n",n);
    if(n < 508079) return 508079;
    else {
        while(1) {
            if(teste_quasePrimo(n)) return (void *)n;
            else n++;
        }
    }
}

int quase_primo(int n) {  
    if(n < 508079) return 508079;
    else {
        while(1) {
        if(teste_quasePrimo(n)) return n;
        else n++;
        }
    }
}


int main(void) {  
    int qtd, n1, n2, n3;
    pthread_t threadA_id, threadB_id, threadC_id;
    void *retornoA, *retornoB;
    int retornoC;

    scanf("%d", &qtd);

    while(1) {
        if(qtd>3) {
            if(scanf("%d", &n1) == EOF) break;
            if(scanf("%d", &n2) == EOF) break;
            if(scanf("%d", &n3) == EOF) break;

            pthread_create(&threadA_id, NULL, calcule_sequaseprimo_maluco, &n1);
            pthread_create(&threadB_id, NULL, calcule_sequaseprimo_maluco, &n2);    
            
            retornoC = quase_primo(n3);
            
            
            pthread_join(threadB_id, &retornoB);
            pthread_join(threadA_id, &retornoA);

            printf("%d\n", (int)retornoA);
            printf("%d\n", (int)retornoB);
            printf("%d\n", retornoC);

            qtd -= 3;
        }
        else {
            if(scanf("%d", &n1) == EOF) break;

            pthread_create(&threadA_id, NULL, calcule_sequaseprimo_maluco, &n1);

            pthread_join(threadA_id, &retornoA);
            printf("%d\n", (int)retornoA);
            
        }
    }
}
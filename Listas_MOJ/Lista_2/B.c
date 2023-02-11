#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void signal_handler(int signum);

int contadorDeSigs = 1;

int main(int argc, char const *argv[]){
    
    signal(SIGUSR1, signal_handler);
    signal(SIGALRM, signal_handler);

    while (contadorDeSigs<4) {
        sleep(1);
    }

    return 0;
}

void signal_handler(int signum){

    if (signum == SIGUSR1) {
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    } else if (signum == SIGALRM && contadorDeSigs == 3) {
        contadorDeSigs++;
        printf("Os incomodados que se mudem, tchau\n");
    } else if (signum == SIGALRM) {
        contadorDeSigs++;
        printf("Ai que sono, quero dormir mais um pouco\n");
    }   
        
}




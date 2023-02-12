#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/shm.h>


int erro;

int main(void) {

    char entrada1[255];
    char entrada2[255];
    pid_t pid = 1;
    struct timeval inicio, fim, inicio2, fim2;
    int shm_id;
    double soma=0;
    int erro;

    // shm_id = shmget(IPC_PRIVATE, 1024, IPC_CREAT |  0660);
    // if (shm_id < 0) {
    //     printf("shmget error\n");
    // }

    // int *shrd = (int*)shmat(shm_id, NULL, 0);

    gettimeofday(&inicio2, NULL);

    while(scanf("%s %s", entrada1, entrada2) != EOF){
        fflush(stdout);
        pid = fork();
        gettimeofday(&inicio, NULL);
        if(pid == 0){            
            execl(entrada1, entrada1, entrada2, NULL);
            if(strerror(errno) != "Success")
                printf("> Erro: %s\n", strerror(errno));
            fflush(stdout);
            erro = errno;
            fclose(stdin);
            exit(errno);
        }
        else{
            waitpid(pid, &erro, WUNTRACED);
            erro = WEXITSTATUS(erro);

            gettimeofday(&fim, NULL);
            
            double periodo = (fim.tv_sec - inicio.tv_sec) + 1e-6*(fim.tv_usec - inicio.tv_usec);
            // printf("%s %s %0.1f\n", entrada1, entrada2, periodo);
            // soma = soma + periodo;
            printf("> Demorou %0.1lf segundos, retornou %i\n", periodo ,erro);
            fflush(stdout);
        }

    }
    gettimeofday(&fim2, NULL);

    double periodo2 = (fim2.tv_sec - inicio2.tv_sec) + 1e-6*(fim2.tv_usec - inicio2.tv_usec);
    if(pid != 0) printf(">> O tempo total foi de %0.1lf segundos\n", periodo2);

    return 0;
}
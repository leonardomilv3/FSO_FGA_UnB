#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara_arquivo(char *filename1, char *filename2, long tam) {
    char c1, c2;
    int validade=0;
    FILE *arquivo1, *arquivo2;

    arquivo1 = fopen(filename1, "r");
    arquivo2 = fopen(filename2, "r");

    for(int i=0; i<tam; i++) {
        c1 = fgetc(arquivo1);
        c2 = fgetc(arquivo2);
        if(c1 != c2) validade = 1;
    }
    return validade;
}

int tam_arquivo(char *filename) {
    FILE *arquivo;
    long tamanho;

    arquivo = fopen(filename, "r");

    if(arquivo != NULL) {
        fseek(arquivo, 0, SEEK_END);
        tamanho = ftell(arquivo);
        fclose(arquivo);
        return tamanho;
    }

    printf("Arquivo inexistente");
    return 0;
}


int main(int argc, char **argv) {
    
    long tam1, tam2;
    int validade;
    for(int i=1; i < argc; i++) {
        tam1 = tam_arquivo(argv[i]);
        
        for(int j=i+1; j < argc; j++){
           tam2 = tam_arquivo(argv[j]);
           if(tam1 == tam2) {
            validade = compara_arquivo(argv[i], argv[j], tam2);
            if(validade == 0) printf("%s %s iguais\n", argv[i], argv[j]);
            else printf("%s %s diferentes\n", argv[i], argv[j]);
            
           } 
           else printf("%s %s diferentes\n", argv[i], argv[j]);
        }
    }
    return 0;
}
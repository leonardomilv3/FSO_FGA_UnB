#include <stdio.h>
#include <stdlib.h>

int lenFrames, lenPages;

void inicialize_array(int *array);
int isPageInArray(int *array, int numPage);
void movePages(int *array, int numPage);


int main(int argc, char const *argv[]){
    
    int numPage, count = 0;

    scanf("%d", &lenFrames);
    scanf("%d", &lenPages);

    int *fifo_array = malloc(lenFrames * sizeof(int));

    inicialize_array(fifo_array);

    while (lenPages >= 1) {

        scanf("%d", &numPage);
        if ( ! isPageInArray(fifo_array, numPage) ) {
            movePages(fifo_array, numPage);
            count++;
        }
        lenPages--;
    }

    printf("%d\n", count);

    return 0;
}


void inicialize_array(int *array) {

    for (int i=0; i<lenFrames; i++) {
        *(array + i) = -1;
    }

}

int isPageInArray(int *array, int numPage){

    int isElementPresent = 0;
     
    for (int i = 0; i < lenFrames; i++) {
        if (array[i] == numPage) {
            isElementPresent = 1;
            break;
        }
    }
    
    if (isElementPresent) return 1;
     
    return 0;
}

void movePages(int *array, int numPage){

    for (int i = 0; i < lenFrames-1; i++) {
        array[i] = array[i+1];
    }

    array[lenFrames-1] = numPage;

}


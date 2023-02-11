#include <stdio.h>
#include <stdlib.h>

int lenFrames, lenPages;

void inicialize_array(int *array);
int isPageInArray(int *array, int *pageCount_array, int numPage);
void movePages(int *array, int *pageCount_array, int numPage);
void insertPageInArray(int *array, int *pageCount_array, int numPage);


int main(int argc, char const *argv[]){
    
    int numPage, count = 0, i=0;

    scanf("%d", &lenFrames);
    scanf("%d", &lenPages);

    int *lru_array = malloc(lenFrames * sizeof(int));
    int *pageCount_array = calloc(lenFrames, sizeof(int));

    inicialize_array(lru_array);

    while ( i < lenPages) {

        scanf("%d", &numPage);

        if ( !isPageInArray(lru_array, pageCount_array, numPage) && i < lenFrames ){
            movePages(lru_array, pageCount_array,numPage);
            count++;
            i++;
            continue;
        }

        if ( !isPageInArray(lru_array, pageCount_array, numPage) ) {
            insertPageInArray(lru_array, pageCount_array,numPage);
            count++;
        }

        i++;
    }

    printf("%d\n", count);
    return 0;
}


void inicialize_array(int *array) {
    for (int i=0; i<lenFrames; i++) {
        *(array + i) = -1;
    }
}

int isPageInArray(int *lru_array, int *pageCount_array, int numPage){

    int isElementPresent = 0;
     
    for (int i = 0; i < lenFrames; i++) {
        if (lru_array[i] == numPage) {
            isElementPresent = 1;
            pageCount_array[i] = 0;
        } else
            pageCount_array[i]++;
    }
    
    if (isElementPresent) return 1;
     
    return 0;
}

void movePages(int *array, int *pageCount_array, int numPage){

    for (int i = 0; i < lenFrames-1; i++) {
        array[i] = array[i+1];
        pageCount_array[i] = pageCount_array[i+1] + 1;
    }

    array[lenFrames-1] = numPage;
    pageCount_array[lenFrames-1] = 0;

}

void insertPageInArray(int *array, int *pageCount_array, int numPage){

    int lru_pageCount = pageCount_array[0], index = 0;

    for (int i=1; i<lenFrames; i++){
        if (lru_pageCount < pageCount_array[i]){
            lru_pageCount = pageCount_array[i];
            index = i;
        } 
    } 

    for (int i=0; i<lenFrames; i++){
        if (i != index)
            pageCount_array[i]++;
    }

    array[index] = numPage;
    pageCount_array[index] = 0;

}
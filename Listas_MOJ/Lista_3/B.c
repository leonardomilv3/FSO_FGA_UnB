#include <stdio.h>
#include <stdlib.h>

int lenFrames;

void inicialize_array(int *array);
int search(int *array, int numPage);
void movePages(int *array, int numPage);
void optimalPage(int *pg, int pn, int fn);
int availableSpaceInArray(int *array);
int predict(int *pg, int *fr, int pn, int index);


int main(int argc, char const *argv[]){
    
    int lenPages, numPage, i=0;

    scanf("%d", &lenFrames);
    scanf("%d", &lenPages);

    int *pg = malloc( lenPages * sizeof(int) );

    while (i < lenPages ) {
        scanf("%d", &numPage);
        pg[i] = numPage;
        i++;
    }

	optimalPage(pg, lenPages, lenFrames);
    free(pg);

    return 0;
}


void inicialize_array(int *array) {

    for (int i=0; i<lenFrames; i++) {
        *(array + i) = -1;
    }
}

int search(int *array, int numPage){

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

void optimalPage(int *pg, int pn, int fn){

	// Create an array for given number of
	// frames and initialize it as empty.

    int *fr = malloc(fn * sizeof(int));

    inicialize_array(fr);

	// Traverse through page reference array
	// and check for miss and hit.
	int hit = 0;
	for (int i = 0; i < pn; i++) {

		// Page found in a frame : HIT
		if (search(fr, pg[i])) {
			hit++;
			continue;
		}

		// Page not found in a frame : MISS

		// If there is space available in frames.
		if (availableSpaceInArray(fr) < fn)
			movePages(fr, pg[i]);

		// Find the page to be replaced.
		else {
			int j = predict(pg, fr, pn, i + 1);
			fr[j] = pg[i];
		}
            
	}
    printf("%d\n", pn-hit);

    free(fr);
}

int predict(int *pg, int *fr, int pn, int index){
	// Store the index of pages which are going
	// to be used recently in future
	int res = -1, farthest = index;                       
	for (int i = 0; i < availableSpaceInArray(fr); i++) { 
		int j;                                             
		for (j = index; j < pn; j++) {                     
			if (fr[i] == pg[j]) {                          
				if (j > farthest) {                        
					farthest = j;                          
					res = i;
				}
				break;
			}
		}

		// If a page is never referenced in future,
		// return it.
		if (j == pn)                                        // 5 == 5
			return i;                                       // i = 0
	}

	// If all of the frames were not in future,
	// return any of them, we return 0. Otherwise
	// we return res.
	return (res == -1) ? 0 : res;
}

void movePages(int *array, int numPage){

    for (int i = 0; i < lenFrames-1; i++) {
        array[i] = array[i+1];
    }

    array[lenFrames-1] = numPage;
}

int availableSpaceInArray(int *array){

    int lenAvailableSpace = 0;
    for (int i = 0; i < lenFrames; i++) {

        if (array[i] != -1) {
            lenAvailableSpace++;
        }
    }
    return lenAvailableSpace;
}

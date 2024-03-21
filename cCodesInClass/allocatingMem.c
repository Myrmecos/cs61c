#include<stdio.h>
#include<stdlib.h>


int ARRSIZE = 5;
int * allocateMem(int numberOfElements) {
    int * ret = malloc(numberOfElements * sizeof(int));
    return ret;
}

int main() {
    printf("Hello World!\n");

    int * ptr = allocateMem(ARRSIZE);
    for (int i = 0; i < ARRSIZE; i ++) {
        *(ptr + i) = i;
    }

    ptr = realloc(ptr, 6*sizeof(int));

    for (int i = 0; i < ARRSIZE; i ++) {
        printf("%d", *(ptr + i));
    }

    free(ptr);
}
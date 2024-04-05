#include <stdio.h>
#define ARRAY_SIZE 5
int main() {
    int a[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    unsigned total = 0;
    for (int j = 0; j < ARRAY_SIZE; j++) {
        total += a[j];
    }
    printf("sum of array is %d\n", total);
}
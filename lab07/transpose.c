#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>



/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    //int chunkSize = blocksize*blocksize;
    int widthAfterBlocking = n/blocksize;
    for (int i = 0; i <= widthAfterBlocking; i++) {
        for (int j = 0; j <= widthAfterBlocking; j++) {
            for (int k = 0; k < blocksize; k++) {
                if (k+i*blocksize >= n) {
                    continue;}
                for (int l = 0; l < blocksize; l++) {
                    if(l+j*blocksize >= n){continue;}
                    //printf("ind: %d, %d ", k+i*blocksize, l+j*blocksize);
                    dst[(l+j*blocksize)*n + k + i*blocksize] = src[(k+i*blocksize)*n + l+j*blocksize];
                    //dst[(j*blocksize+l)*blocksize*widthAfterBlocking+i*blocksize+k]=src[(i*blocksize+k)*blocksize*widthAfterBlocking+j*blocksize+l];
                    //dst[(i*blocksize+k)*blocksize*widthAfterBlocking+j*blocksize+l]=src[(i*blocksize+k)*blocksize*widthAfterBlocking+j*blocksize+l];
                }
            }
        }
    }
}

int calculatePosition(int n, int blocksize, int i, int j, int k, int l) {
    return 0;
}

void benchmark(int *A, int *B, int n, int blocksize,
    void (*transpose)(int, int, int*, int*), char *description) {

    int i, j;
    printf("Testing %s: ", description);

    /* initialize A,B to random integers */
    srand48( time( NULL ) );
    for( i = 0; i < n*n; i++ ) A[i] = lrand48( );
    for( i = 0; i < n*n; i++ ) B[i] = lrand48( );

    /* measure performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );

    double seconds = (end.tv_sec - start.tv_sec) +
        1.0e-6 * (end.tv_usec - start.tv_usec);
    printf( "%g milliseconds\n", seconds*1e3 );


    /* check correctness */
    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            if( B[j+i*n] != A[i+j*n] ) {
                printf("Error!!!! Transpose does not result in correct answer!!\n");
                exit( -1 );
            }
        }
    }
}

void print(int * toPrint, int width) {
    for (int i = 0; i < width; i ++) {
        for (int j = 0; j < width; j++) {
            printf("%d\t", toPrint[i*width + j]);
        }
        printf("\n");
    }
}

void test(void) {
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int b[9];
    transpose_blocking(3, 2, b, a);
    print(b, 3);
    
}

int main( int argc, char **argv ) {
    //test();
    if (argc != 3) {
        printf("Usage: transpose <n> <blocksize>\nExiting.\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int blocksize = atoi(argv[2]);

    /* allocate an n*n block of integers for the matrices */
    int *A = (int*)malloc( n*n*sizeof(int) );
    int *B = (int*)malloc( n*n*sizeof(int) );

    /* run tests */
    benchmark(A, B, n, blocksize, transpose_naive, "naive transpose");
    benchmark(A, B, n, blocksize, transpose_blocking, "transpose with blocking");

    /* release resources */
    free( A );
    free( B );
    return 0;
}

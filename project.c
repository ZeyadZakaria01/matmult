#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]

extern void matmult(int *A, int *B, int *C, int l, int m, int n);
extern void matmult_v1(int *A, int *B, int *C, int l, int m, int n);
extern void matmult_v2(int *A, int *B, int *C, int l, int m, int n);
extern void printMatrices(int *A, int *B, int *C, int l, int m, int n);
void populateMatrix(int *X, int nrow, int ncol);
void printMatrix(int *X, int nrow, int ncol);
int main()
{
    // int l = 3, m = 4, n = 5;
    int l = 200, m = 500, n = 160;
    // int l = 2000, m = 1000, n = 2000;
    int *A = (int *)malloc(l * m * sizeof(int));
    int *B = (int *)malloc(m * n * sizeof(int));
    int *C = (int *)malloc(l * n * sizeof(int));

    populateMatrix(A, l, m);
    populateMatrix(B, m, n);

    // Calculate the time taken
    // clock_t t;
    // double time_taken;
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmult(A, B, C, l, m, n);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("matmult took %f seconds to execute \n", elapsed);
    // printMatrices(A, B, C, l, m, n);

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmult_v1(A, B, C, l, m, n);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("matmult_v1 took %f seconds to execute \n", elapsed);
    // printMatrices(A, B, C, l, m, n);

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmult_v2(A, B, C, l, m, n);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("matmult_v2 took %f seconds to execute \n", elapsed);
    // printMatrices(A, B, C, l, m, n);

    free(A);
    free(B);
    free(C);

    return 0;
}

/*
 * fill in a matrix with random numbers
 */
void populateMatrix(int *X, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++)
        for (int j = 0; j < ncol; j++)
            Item(X, i, j, ncol) = (((long)X) + ((long)&nrow) + ((long)&nrow) - (~(i * ncol + nrow) + (j * nrow + ncol))) % 29311 % 10;
}

/*
 * prints a matrix on stdout
 */
void printMatrix(int *X, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
            printf("%d\t", Item(X, i, j, ncol));
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

void printMatrices(int *A, int *B, int *C, int l, int m, int n)
{
    printf("A=\n");
    printMatrix(A, l, m);

    printf("B=\n");
    printMatrix(B, m, n);

    printf("C=\n");
    printMatrix(C, l, n);
}
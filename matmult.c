#include <stdlib.h>
#include <pthread.h>

#include <stdio.h>

#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int *A, int *B, int *C, int l, int m, int n)
{
    for (int i = 0; i < l; i++)
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}

/*
 * Arguments to pass it to routines of threads
 *      pointers to 3 matrices A, B & C
 *      size of the 3 matrices
 *      idx of row & column to be printed
 */

typedef struct arguments
{
    int *A, *B, *C;
    int i, j, l, n, m;
} arguments;

arguments *get_arguments_ptr(int *A, int *B, int *C, int l, int m, int n, int i, int j)
{
    arguments *args = malloc(sizeof(arguments));
    args->A = A, args->B = B, args->C = C;
    args->l = l, args->n = n, args->m = m;
    args->i = i, args->j = j;
    return args;
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void *routine_v1(void *arg)
{
    arguments args = *(arguments *)arg;
    int sum = 0;
    for (int k = 0; k < args.m; k++)
        sum += Item(args.A, args.i, k, args.m) * Item(args.B, k, args.j, args.n);
    Item(args.C, args.i, args.j, args.n) = sum;
    pthread_exit(arg);
}

void matmult_v1(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t th[l][n];

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arguments *args = get_arguments_ptr(A, B, C, l, m, n, i, j);
            if (pthread_create(&th[i][j], NULL, &routine_v1, args) != 0)
            {
                printf("args=%p\n[%d][%d]: ", args, i, j);
                perror("Failed to create thread\n");
                pthread_exit(0);
            }
        }
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arguments *args;
            if (pthread_join(th[i][j], (void **)&args) != 0)
            {
                perror("Failed to join thread\n");
                pthread_exit(0);
            }
            free(args);
        }
    }
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

void *routine_v2(void *arg)
{
    arguments args = *(arguments *)arg;
    for (int j = 0; j < args.n; j++)
    {
        int sum = 0;
        for (int k = 0; k < args.m; k++)
            sum += Item(args.A, args.i, k, args.m) * Item(args.B, k, j, args.n);
        Item(args.C, args.i, j, args.n) = sum;
    }
    pthread_exit(arg);
}
void matmult_v2(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t th[l];

    for (int i = 0; i < l; i++)
    {

        arguments *args = get_arguments_ptr(A, B, C, l, m, n, i, 0);
        if (pthread_create(&th[i], NULL, &routine_v2, args) != 0)
        {
            printf("args=%p\n[%d]: ", args, i);
            perror("Failed to create thread\n");
            pthread_exit(0);
        }
    }

    for (int i = 0; i < l; i++)
    {
        arguments *args;
        if (pthread_join(th[i], (void **)&args) != 0)
        {
            perror("Failed to join thread\n");
            pthread_exit(0);
        }
        free(args);
    }
}
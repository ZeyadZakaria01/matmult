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
 *      idx of row & column to be printed
 */
typedef struct iterator
{
    int i, j, l;
} iterator;

iterator *get_iterator_ptr(int i, int j)
{
    iterator *args = malloc(sizeof(iterator));
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
int *A_v1, *B_v1, *C_v1;
int l_v1, m_v1, n_v1;

void *routine_v1(void *arg)
{
    iterator args = *(iterator *)arg;
    int sum = 0;
    for (int k = 0; k < m_v1; k++)
        sum += Item(A_v1, args.i, k, m_v1) * Item(B_v1, k, args.j, n_v1);
    Item(C_v1, args.i, args.j, n_v1) = sum;
    pthread_exit(arg);
}

void matmult_v1(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t th[l][n];

    A_v1 = A, B_v1 = B, C_v1 = C;
    l_v1 = l, m_v1 = m, n_v1 = n;

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            iterator *args = get_iterator_ptr(i, j);
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
            iterator *args;
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
int *A_v2, *B_v2, *C_v2;
int l_v2, m_v2, n_v2;

void *routine_v2(void *arg)
{
    iterator args = *(iterator *)arg;
    for (int j = 0; j < n_v2; j++)
    {
        int sum = 0;
        for (int k = 0; k < m_v2; k++)
            sum += Item(A_v2, args.i, k, m_v2) * Item(B_v2, k, j, n_v2);
        Item(C_v2, args.i, j, n_v2) = sum;
    }
    pthread_exit(arg);
}
void matmult_v2(int *A, int *B, int *C, int l, int m, int n)
{
    pthread_t th[l];

    A_v2 = A, B_v2 = B, C_v2 = C;
    l_v2 = l, m_v2 = m, n_v2 = n;

    for (int i = 0; i < l; i++)
    {

        iterator *args = get_iterator_ptr(i, 0);
        if (pthread_create(&th[i], NULL, &routine_v2, args) != 0)
        {
            printf("args=%p\n[%d]: ", args, i);
            perror("Failed to create thread\n");
            pthread_exit(0);
        }
    }

    for (int i = 0; i < l; i++)
    {
        iterator *args;
        if (pthread_join(th[i], (void **)&args) != 0)
        {
            perror("Failed to join thread\n");
            pthread_exit(0);
        }
        free(args);
    }
}
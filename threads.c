#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *routine()
{
    printf("Hi from routine\n");
}

int main()
{

    pthread_t th[1000][1000];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if (pthread_create(&th[i][j], NULL, &routine, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
        for (int j = 0; j < 100; j++)
        {
            if (pthread_join(th[i][j], NULL) != 0)
            {
                perror("Failed to join thread");
            }
        }
    }
}
#include <time.h>
#include <stdio.h>
#define SIZE 1024

/* void TimerStart(unsigned long* delay1, unsigned long* delay2) */
/* { */
    
/* } */

/* void TimerStop() */
/* { */

/* } */

void CopyAB(int a[SIZE][SIZE], int b[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i ++)
    {
        for (int j = 0; j < SIZE; j ++)
        {
            /* b[i][j] = a[i][j]; */
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
}

void CopyBA(int a[SIZE][SIZE], int b[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i ++)
    {
        for (int j = 0; j < SIZE; j ++)
        {
            a[i][j] = b[i][j];
        }
    }
}

int main()
{
    /* const int size = 1024; */
    unsigned long delay1, delay2;
    int src[SIZE][SIZE];
    int dst[SIZE][SIZE];

    /* TimerStart(); */
    CopyAB(src, dst);
    /* delay1 = TimerStop(); */


    /* TimerStart(); */
    /* CopyBA(src, dst); */
    /* delay2 = TimerStop(); */

    /* printf("Delay1: %lu \n", delay1); */
    /* printf("Delay2: %lu \n", delay2); */

    return 0;
}

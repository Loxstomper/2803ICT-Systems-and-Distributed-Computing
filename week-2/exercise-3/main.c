#include <time.h>
#include <stdio.h>

/* can only use a 'small' size, otherwise stack overflow occurs, would be better to dynamically allocate to */ 
/* the heap */
#define SIZE 1023 

void TimerStart(struct timespec* before)
{
    clock_gettime(CLOCK_MONOTONIC, before);
}

unsigned long TimerStop(struct timespec* before)
{
    struct timespec after;

    clock_gettime(CLOCK_MONOTONIC, &after);

    return after.tv_nsec - before->tv_nsec;
}

void CopyAB(int a[SIZE][SIZE], int b[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i ++)
    {
        for (int j = 0; j < SIZE; j ++)
        {
            b[i][j] = a[i][j];
        }
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
    unsigned long delay1, delay2;
    int src[SIZE][SIZE];
    int dst[SIZE][SIZE];
    struct timespec before;

    TimerStart(&before);
    CopyAB(src, dst);
    delay1 = TimerStop(&before);


    TimerStart(&before);
    CopyBA(src, dst);
    delay2 = TimerStop(&before);

    printf("Delay1 (ns): %lu \n", delay1);
    printf("Delay2 (ns): %lu \n", delay2);



    return 0;
}

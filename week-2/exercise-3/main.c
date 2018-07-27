#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* can only use a 'small' size, otherwise stack overflow occurs, would be better to dynamically allocate to */ 
/* the heap */
#define SIZE 512    
/* int src[SIZE][SIZE]; */
/* int dst[SIZE][SIZE]; */

#ifdef __linux__
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
#endif

#ifdef __win32

#endif

void CopyAB(int** a, int** b)
{
    for (int i = 0; i < SIZE; i ++)
    {
        for (int j = 0; j < SIZE; j ++)
        {
            b[i][j] = a[i][j];
        }
    }
}

void CopyBA(int** a, int** b)
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
    /* int src[SIZE][SIZE]; */
    /* int dst[SIZE][SIZE]; */

#ifdef __linux__
    struct timespec before;
#endif

#ifdef __win32
    struct sdadsadsads before;
#endif

    int ** src = (int**) malloc (sizeof(int*) * SIZE);
    int ** dst = (int**) malloc (sizeof(int*) * SIZE);

    for (int i = 0; i < SIZE; ++i)
    {
        src[i] = (int*) malloc (sizeof(int) * SIZE);
        dst[i] = (int*) malloc (sizeof(int) * SIZE);
    }

    int ** c = (int**) malloc (sizeof(int*) * 4096);

    for (int i = 0; i < 4096; ++i)
    {
        c[i] = (int*) malloc (sizeof(int) * 4096);
    }

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

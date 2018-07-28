
#ifdef __linux__
#include <time.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

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

#ifdef _WIN32 
void TimerStart(__int64* freq, __int64* start)
{
    QueryPerformanceFrequency((LARGE_INTEGER*) freq);
    QueryPerformanceFrequency((LARGE_INTEGER*) start);

}

double TimerStop(__int64* freq, __int64* end, __int64* start)
{
    QueryPerformanceCounter((LARGE_INTEGER*) end);
    return ((*end-*start) * 1000) / *freq;
}

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
    /* int src[SIZE][SIZE]; */
    /* int dst[SIZE][SIZE]; */

#ifdef __linux__
    struct timespec before;
    unsigned long delay1, delay2;
#endif

#ifdef __WIN32 
    __int64 freq, start, end;
    double delay1, delay2;
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

#ifdef __linux__
    TimerStart(&before);
    CopyAB(src, dst);
    delay1 = TimerStop(&before);

    TimerStart(&before);
    CopyBA(src, dst);
    delay2 = TimerStop(&before);

    printf("Delay1 (ns): %lu \n", delay1);
    printf("Delay2 (ns): %lu \n", delay2);
#endif

#ifdef _WIN32 
    TimerStart(&freq, &start);
    CopyAB(src, dst);
    delay1 = TimerStop(&freq, &end, &start);

    TimerStart(&freq, &start);
    CopyBA(src, dst);
    delay2 = TimerStop(&freq, &end, &start);

    printf("Delay1 (ns): %lu \n", delay1);
    printf("Delay2 (ns): %lu \n", delay2);
    
#endif


    return 0;
}

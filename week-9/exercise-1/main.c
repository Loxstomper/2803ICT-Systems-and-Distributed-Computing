#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

struct Args
{ 
    unsigned long long int n;
    unsigned long long int start;
    unsigned long long int end;
    int thread_n;
};


void* factor(void* args)
{
    struct Args* arg = (struct Args*)args;
    unsigned long long int n = arg->n;

    printf("Thread: %d\tStart: %lld\tEnd: %lld\n", arg->thread_n, arg->start, arg->end);
    usleep(1000);

    for (unsigned long long int i = arg->start; i <= arg->end; ++i)
    {
        if (n % i == 0)
        {
            printf("\nThread %d \t %lld", arg->thread_n, i);
        }
    }

    printf("\nThread %d done", arg->thread_n);
}


int main(int argc, char** argv)
{
    /* long long int number = strtoll(argv[1], argv[2], 8); */
    /* int n_threads = atoi(argv[2]); */
    
    long long int number = 4294967134;
    /* unsigned long long int number = 1 << 25; */
    int n_threads = 4;

    printf("\nNumber: %lld \t Threads: %d \n\n", number, n_threads);

    struct Args args;
    args.n = number;
    args.thread_n = 1;
    args.start = 1;
    args.end = number;

    struct Args thread_args[4];
    pthread_t threads[4];

    /* should be floor division */
    unsigned long long int range = (number / 2) / n_threads;

    for (int i = 0; i < n_threads; i ++)
    {
        thread_args[i].n = number;
        thread_args[i].thread_n = i;

        if (i == 0)
        {
            thread_args[i].start = 1;
            thread_args[i].end = thread_args[i].start + range - 1;
        }
        else
        {
            thread_args[i].start = thread_args[i - 1].end + 1;
            thread_args[i].end = thread_args[i].start + range - 1;
        }

        /* pthread_t tid; */
        if (pthread_create(&threads[i], NULL, factor, (void*)&thread_args[i]))
        {
            printf("FAILED TO CREATE THREAD: %d\n", i);
            return -1;
        }
    }

    /* join the threads */
    for (int i = 0; i < n_threads; i ++)
    {
        if(pthread_join(threads[i], NULL))
        {
            printf("FAILED TO JOIN THREAD: %d\n", i);
            return -1;
        }

        pthread_detach(threads[i]);
    }

    printf("\n");

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct Args
{ 
    long long int n;
    long long int start;
    long long int end;
    int thread_n;
};


void* factor(void* args)
{
    usleep(1000);
    struct Args* arg = (struct Args*)args;
    long long int n = arg->n;

    printf("Thread: %d\tStart: %lld\tEnd: %lld\n", arg->thread_n, arg->start, arg->end);

    for (long long int i = arg->start; i <= arg->end; ++i)
    {
        if (n % i == 0)
        {
            printf("Thread %d \t %lld \n", arg->thread_n, i);
        }
    }

    printf("Thread %d done\n", arg->thread_n);
}


int main(int argc, char** argv)
{
    /* long long int number = strtoll(argv[1], argv[2], 8); */
    /* int n_threads = atoi(argv[2]); */
    
    long long int number = 24;
    int n_threads = 4;

    printf("Number: %lld \t Threads: %d \n", number, n_threads);

    printf("THE MAIN\n");

    struct Args args;
    args.n = number;
    args.thread_n = 1;
    args.start = 1;
    args.end = number;

    struct Args thread_args[4];
    pthread_t threads[4];

    /* should be floor division */
    long long int range = number / n_threads;

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

    return 0;
}


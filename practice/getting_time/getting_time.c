#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <time.h>
void start_timer(struct timespec* before)
{
    clock_gettime(CLOCK_MONOTONIC, before);
}

unsigned long stop_timer(struct timespec* before)
{
    struct timespec after;

    clock_gettime(CLOCK_MONOTONIC, &after);

    return (after.tv_nsec - before->tv_nsec) * 1E9;
}

void current_time()
{
    printf("GETTING TIME");
    time_t curr;
    char* c_time_string;

    curr = time(NULL);

    if (curr == ((time_t)-1))
    {
        printf("Failed to get current time\n");
        exit(EXIT_FAILURE);
    }

    c_time_string = ctime(&curr);

    if (c_time_string == NULL)
    {
        printf("Failed to convert the current time\n");
        exit(EXIT_FAILURE);
    }

    printf("Current time: %s\n", curr);
}


#else
#endif

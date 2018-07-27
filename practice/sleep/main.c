/* takes command line argument and sleeps for that amount of time */
#include <stdlib.h>
#include <stdio.h>

#ifdef __linux__
#include <unistd.h>
#else
#include <windows.h>
#endif

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        return 1;
    }

    int sleep_time = atoi(argv[1]);

    printf("Going to sleep for %d seconds.\n", sleep_time);

#ifdef __linux__
    sleep(sleep_time);
#else
    Sleep(sleep_time);
#endif

    printf("Im awake\n");

    return 0;
}

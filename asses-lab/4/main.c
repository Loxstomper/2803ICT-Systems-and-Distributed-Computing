#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define DEBUG 0

// calculates the points, and stores the value in points_in[i] where i is the thread number (logical)
void* generate_points(void* id)
{
    int points_in = 0;
    int x, y;
    int distance;

    int c_x = 10;
    int c_y = 10;
    int radius = 10;

    // set up the random number generator
    srand(pthread_self());

    int loop_count = 100;

    for (int i = 0; i < loop_count; i ++)
    {
        x = rand() % 21;
        y = rand() % 21;

        // determine if point falls in circle within the square 
        // square centre is 10, 10 and radius of 10
        distance = sqrt(pow((c_x - x), 2) + pow((c_y - y), 2));

        if (distance < radius)
        {
            points_in ++;
        }
    }

    // this pointer is points_in[i] from the main function
    *(int *)id = points_in;
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: a.out NUM_THREADS [b]\n");
        exit(1);
    }

    int n_threads = atoi(argv[1]);
    // using calloc because it is very unlikely that a point does not fall in the range
    int* in_square = calloc(n_threads, sizeof(int));

    int b_flag = (argc > 2 && *argv[2] == 'b');

    long double PI_VALUE = 3.1415926535897932384626433832795;
    long double calculated_pi;
    long double error;
    char output[1024];

    int completed_threads = 0;
    long long sum;
    int is_update = 0;
    int last_completed_threads;

    pthread_t tid[n_threads];

    // for (int i = 0; i < n_threads; i ++)
    // {
    //     printf("%d ", tid[i]);
    // }

    printf("\n");

    // create the threads
    for (int i = 0; i < n_threads; i ++)
    {
        sum = 0;

        pthread_create(&tid[i], NULL, generate_points, (void*)&in_square[i]);
        // pthread_join(tid[i], NULL);
        // pthread_detach(tid[i]);

        // DONT JOIN
    }


    while (completed_threads < n_threads)
    {
        sum = 0;
        completed_threads = 0;
        // now can do some output
        for (int i = 0; i < n_threads; i ++)
        {
            if (in_square[i] != 0)
            {
                sum += in_square[i];
                completed_threads ++;
            }
        }

        is_update = 0;

        if (last_completed_threads != completed_threads)
        {
            is_update = 1;
        }

        last_completed_threads = completed_threads;

        
        if (is_update)
        {
            calculated_pi = 4.0 * (sum) / (100.0 * completed_threads);
            error = ((calculated_pi - PI_VALUE) / PI_VALUE) * 100.0;

            if (!b_flag)
            {
                printf("%d) PI = %Lf \t Error = %Lf%\n", completed_threads, calculated_pi, error);
            }
            else
            {
                // clears the line
                // printf("\33[2K\r");
                printf("\r");
                printf("Progress: %f ", 100.0 * completed_threads / n_threads);

                // really should max a max length bar
                // max length of 10

                for (int k = 0; k < completed_threads; k ++)
                {
                    printf("▒");
                }

                for (int l = completed_threads; l < n_threads; l ++)
                {
                    printf("_");
                }

                printf("| PI = %Lf Error = %Lf%", calculated_pi, error);
            }
        }

        // if (DEBUG)
        // { 
        //     printf("THREAD ID: %d \n", tid[i]);
        //     printf("SUM: %d \n", sum);
        //     printf("4.0 * sum: %f\n", 4.0 * sum);
        //     // printing the contents of in_square
        //     for (int k = 0; k < n_threads; k ++)
        //     {
        //         printf("%d ", in_square[k]);
        //     }
        //     printf("\n");
        // }

    }

    printf("\n");

    return 0;
}
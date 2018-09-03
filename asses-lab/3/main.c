#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

#define BUFFER_SIZE 1024

/* just fork once, no zombies, parent will loop a lot */

int main(int argc, char** argv)
{
    char buffer[BUFFER_SIZE];
    pid_t child_pid;
    int p1[2], p2[2];

    // no zombies
    signal(SIGCHLD, SIG_IGN);


    // check the pipes are ok
    if (pipe(p1) != 0)
    {
        perror("p1 error");
        exit(1);
    }
    if (pipe(p2) != 0)
    {
        perror("p2 error");
        exit(1);
    }

    // create the child
    if ((child_pid = fork()) == 0)
    {
        while (1)
        {
            close(p1[1]);
            close(p2[0]);

            if (read(p1[0], buffer, BUFFER_SIZE) == -1)
            {
                perror("read() error in parent");
                exit(1);
            }
            else
            {
                if (write(p2[1], "im the child\n", sizeof("im the child\n") + 1) == -1)
                {
                    perror("write() error in child");
                    exit(1);
                }
            }
        }

        exit(0);

        // while (1)
        // {
            // wait to read the pipe
            // perform evaluation
            // write to the pipe
        // }

    }
    else
    {
        while (1)
        {
            printf("im the parent\n");
            close(p1[0]);
            close(p2[1]);

            printf("Expression: ");

            fgets(buffer, BUFFER_SIZE, stdin);

            printf("Parenting writing to pipe1\n");
            if (write(p1[1], buffer, strlen(buffer) + 1) == -1)
            {
                perror("write() error in parent");
                exit(1);
            }
            else if (read(p2[0], buffer, BUFFER_SIZE) == -1)
            {
                perror("read() error in parent");
                exit(1);
            }
            else
            {
                printf("Parent read: %s\n", buffer);
            }
        }

        // write to the pipe
        // print from the pipe output
    }



    

    return 0;
}
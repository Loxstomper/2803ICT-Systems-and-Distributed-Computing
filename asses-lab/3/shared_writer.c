#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER_SIZE 1024


int main(int argc, char** argv)
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
 
    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);
 
    char* buffer;
    char first_char;

    printf("\n");

    while (1)
    {
        // shmat to attach to shared memory
        buffer = (char*) shmat(shmid,(void*)0,0);

        printf("Expression: ");

        fgets(buffer, BUFFER_SIZE, stdin);
        // fgets adds new line char
        buffer[strlen(buffer) - 1] = '\0';
        first_char = buffer[0];

        // printf("Data written in memory: %s\n",buffer);

        while (buffer[0] == first_char)
        {
            // wait
        }

        // the reader should have wrote back with the answer
        printf("Result    : %s\n\n", buffer);

        // detach
        shmdt(buffer);

    }

    return 0;
}

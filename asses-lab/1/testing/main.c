#include <stdio.h>
#include <string.h>

int main()
{
    char line[1024];
    char command[1024];
    char* args[1024];
    char * tmp;
    int count;

    while (1)
    {
        count = 0;
        printf("$: ");

        scanf("%s", line);

        printf("LINE: %s \n", line);

        tmp = strtok(line, " ");

        while (tmp != NULL)
        {
            printf("TESTING %d: %s\n", count, tmp);
            tmp = strtok(NULL, " ");
            count ++;
        }

        printf("\n\n\n");
    }

    return 0;
}

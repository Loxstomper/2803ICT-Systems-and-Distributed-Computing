#include <stdlib.h>
#include <stdio.h>

/* cross platform */
void get_dump(char* path)
{
    FILE* target;
    char c;

    target = fopen(path, "r");

    while ((c = fgetc(target)) != EOF)
    {
        printf("%c", c);
    }

    printf("\n");
}

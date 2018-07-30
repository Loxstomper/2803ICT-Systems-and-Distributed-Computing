#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int compare(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    /* reverse order */
    return strcmp(*ib, *ia);
}


/* read all files into a buffer and perform qsort then print */
#include <dirent.h>
void get_cur_files()
{
    struct dirent *entry;
    DIR *dp;

    char* buffer[1024];
    int count = 0;

    dp = opendir(".");

    if (dp != NULL)
    {
        while((entry = readdir(dp)))
        {
            count ++;
            /* this line is causing seg faults */
            /* do i need to do a malloc of size entry->d_name? */
            /* buffer[count] = entry->d_name; */
            printf("%s\n", entry->d_name);
        }

        printf("\n");

        /* printf("Before qsort\n"); */
        /* qsort(buffer, sizeof(buffer) / sizeof(char *), sizeof(char *), compare); */
        /* printf("After qsort\n"); */


        /* for (int i = 0; i < count; i ++) */
        /* { */
        /*     printf("%s\n", buffer[i]); */
        /* } */
        
        /* printf("\n"); */
    }

    closedir(dp);
}

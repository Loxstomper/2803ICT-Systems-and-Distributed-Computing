/* this is terrible, sorry I couldnt think properly */
/* read in line -> split into command and array of args */
/* read what the command is and execute according function, if it requires args pass through the args */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dump.h"
#include "misc.h"
#include "listing.h"

// didnt end up using
char* get_arg(char* in)
{
    // find first white space, read to \0 and return
    char *token;
    const char delim[2] = " ";

    token = strtok(in, " ");

    if (token != NULL)
    {
        token = strtok(NULL, token);
        printf("ARG: %s\n", token);
        return token;
    }
    
    return "test";
}

/* windows and *nix */
void get_cur_time()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s\n", asctime(tm));
}

int main(int argc, char ** argvc)
{
    /* use a split function to get the args */
    char line[1024];
    char command[1024];
    char arg[1024];
    char* test;


    /* char testing[] = "COMMAND ARGS"; */
    /* get_arg(testing); */


    while (1)
    {
        printf("$: ");
        /* scanf("%s", line); */
        scanf("%s", command);

        /* this wasnt working, was restarting the outer loop */
        /* split into command and arg */
        /* test = strtok(line, " "); */
        /* while (test != NULL) */
        /* { */
        /*     printf("%s\n", test); */
        /*     test = strtok(NULL, " "); */
        /* } */


        if(strcmp(command, "calc") == 0)
        {
            /* using dummy data */
            char* exp[] = {"+", "5", "2"};
            int first = 0;
            int res = prefix(&first, 2, exp);
            printf("%d\n", res); 
        }
        if(strcmp(command, "time") == 0)
        {
            get_cur_time();
        }
        if(strcmp(command, "path") == 0)
        {
            get_path();
        }
        if(strcmp(command, "dump") == 0)
        {
            /* couldnt seperate command from args :( */
            char* path;
            scanf("%s", path);
            get_dump(path);
        }
        if(strcmp(command, "list") == 0)
        {
            get_cur_files();
        }
        /* else */
        /* { */
        /*     printf("Invalid command.\n"); */
        /* } */
    }


    return 0;
}

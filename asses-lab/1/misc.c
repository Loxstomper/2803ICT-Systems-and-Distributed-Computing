#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* void get_cur_time() */
/* { */
/*     time_t t = time(NULL); */
/*     struct tm *tm = localtime(&t); */
/*     printf("%s\n", asctime(tm)); */
/* } */

#ifdef __linux__

#include <unistd.h>
void get_path()
{
    char buffer[1024];
    getcwd(buffer, sizeof(buffer));
    printf("%s\n", buffer);
}

#else

#include <windows.h>
void get_path()
{
    char buffer[1024];
    GetModuleFileName(NULL, buffer, sizeof(buffer));
    printf("%s\n", buffer);
}

#endif

int prefix(int *curr_index, int last_index, char *argv[])
{
    if (*curr_index > last_index) return 1;

    if (strlen(argv[*curr_index]) == 1 && *(argv[*curr_index]) == '+')
    {
        (*curr_index) ++;
        int operand1 = prefix(curr_index, last_index, argv);
        (*curr_index) ++;
        int operand2 = prefix(curr_index, last_index, argv);

        return operand1 + operand2;
    }
    else
    {
        int result = atoi(argv[*(curr_index)++]);
        return result;
    }
}

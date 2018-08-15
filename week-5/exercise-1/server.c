#include "common.h"

#include <time.h>

char* get_system_time()
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return asctime(timeinfo);
}

void get_host_name(char* buffer, int buff_size)
{
    gethostname(buffer, buff_size);
}

char* get_OS_type()
{
    #ifdef __linux__
    return "linux";
    #else
    return "windows";
    #endif
}

int main(int argc, char ** argv)
{
    char buff[1024];
    get_host_name(buff, 1024);
    printf("NAME: %s\n", buff);
    /* printf("TIME: %s\n", get_system_time()); */
    return 0;
}

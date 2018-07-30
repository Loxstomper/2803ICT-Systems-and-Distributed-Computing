#include <stdio.h>

#ifdef __linux__
#include <unistd.h>
#include <sys/stat.h>

void get_platform()
{
    printf("This is Linux!\n");
}

void get_cwd()
{
    char buff[1024];

    getcwd(buff, sizeof(buff));

    printf("Current directory: %s \n", buff);
}

long int get_file_size(const char* f)
{
    struct stat st;

    if (stat(f, &st) == 0)
    {
        return st.st_size;
    }

    printf("FUCK\n");
    printf("test: %a \n", st);

    return -1;
}

#else
#include <windows.h>
#include <direct.h>

void get_platform()
{
    printf("This is Windows!\n");
}

void get_cwd()
{
    wchar_t path[1024];

    _wgetcwd(path, sizeof(path));
    /* path = _wgetcwd(NULL, sizeof(path)); */

    printf("Current directory: %s \n", path);
}

/* long int get_file_size(); */

#endif

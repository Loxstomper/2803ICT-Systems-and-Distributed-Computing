#include <stdio.h>
#include "stuff.h"


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("./out FILE_NAME\n");
        return -1;
    }

    get_platform();
    get_cwd();

    /* long int s = get_file_size(argv[1]); */

    /* printf("%s : %ld bytes\n", argv[1], s); */

    return 0;
}

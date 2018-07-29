#include "getting_time.h"
#include <stdio.h>


int main(int argc, char ** argv)
{
    int tmp;

    /* start_timer(); */

    current_time();

    scanf("%d", &tmp);

    /* stop_timer(); */

    printf("Time ran: \n");

    return 0;
}

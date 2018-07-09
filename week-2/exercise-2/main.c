#include <stdio.h>
#include "Include.h"

#define MAXLEN 1000

int main()
{
    char instring[MAXLEN];
    printf("Enter a string with leading and trialing blanks:\n");
    gets(instring);
    printf("input = '%s'\n", instring);
    leading(instring);
    trailing(instring);
    printf("output = '%s'\n", instring);

    return 0;
}

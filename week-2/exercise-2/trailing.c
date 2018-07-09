#include <strings.h>

#define MAXLEN 1000

void trailing(char *s)
{
    int index = MAXLEN;

    int slength = strlen(s) - 1;

    while ((s[slength] == ' ' || s[slength] == '\t'))
    {
        --slength;
    }

    s[++slength] = '\0';
}

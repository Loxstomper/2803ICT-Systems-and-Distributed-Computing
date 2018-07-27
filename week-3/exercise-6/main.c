#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ParseLine(char* src, char delim, char* tokens[], int max_tkns)
{
    int count = 0;
    int i = 0;

    while (src[i] != '\0')
    {
        if (src[i] == delim && count < max_tkns)
        {
            count ++;
            tokens[count] = src[i];
        }

        i ++;
    }

    return count;
}

int main(int argc, char ** argv)
{
    char user_input[50];
    char delim;
    char garbage;
    int max_tkns = 100;
    char* tokens[max_tkns];

    printf("String: ");
    scanf("%s", user_input);
    printf("\ndelim: ");
    scanf("%c%c", &garbaga, &delim);

    printf("...: %c\n", delim);

    int n;

    n = ParseLine(user_input, delim, tokens, max_tkns);

    printf("\n%d", n);

    return 0;
}

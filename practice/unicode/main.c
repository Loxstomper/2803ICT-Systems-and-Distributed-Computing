#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char ** argv)
{
    setlocale(LC_ALL, "en_AU");

    FILE* in;

    wint_t c;

    in = fopen("unicode.txt", "r");

    while ((c = fgetwc(in)) != WEOF)
    {
        printf("%lc", c);
    }
    
    printf("\n");


    return 0;
}

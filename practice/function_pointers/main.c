#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int x_squared(int x)
{
    return x * x;
}

void print_x(int x)
{
    printf("x: %d \n", x);
}

int to_be_handled(int a, int b, int c)
{
    return a * b + c;
}

void handler(int (*x)(int, int, int), int a, int b, int c)
{
    printf("%d\n", (*x)(a, b, c));
}


int main(int argc, char ** argv)
{

    void (*p)(int) = &print_x;

    (*p)(10);

    int (*x)(int) = &x_squared;

    int l = (*x)(2);

    printf("%d", l);

    int (*a)(int, int) = &add;

    printf("\n%d\n", (*a)(3, 5));

    int (*t)(int, int, int) = to_be_handled;

    handler(t, 1, 2, 3);

    return 0;
}

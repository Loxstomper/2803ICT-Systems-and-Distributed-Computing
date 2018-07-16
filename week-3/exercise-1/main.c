#include <stdio.h>
#include <math.h>

void get_input(int* start_x, int* end_x, int* step_x, int* function)
{
    printf("Please enter the starting value of x: ");
    scanf("%d", start_x);

    printf("Please enter the final value of x   : ");
    scanf("%d", end_x);

    printf("Please enter the step size of x     : ");
    scanf("%d", step_x);

    printf("Please select one of the following functions: \n");
    printf("1. sin(x)\n2. cos(x)\n3. tan(x)\n4. log(x)\n5. square root(x)\n6. x*x\n7. x*x*x\n8. 2*x*x-3*x\n9. 1/x\n10. 1/(x*x)\n");
    scanf("%d", function);
}

double calculate(double x, int* function)
{
    switch (*function)
    {
        case 1: return sin(x);
        case 2: return cos(x);
        case 3: return tan(x);
        case 4: return log(x);
        case 5: return sqrt(x);
        case 6: return x * x;
        case 7: return x * x * x;
        case 8: return 2 * x * x - 3 * x;
        case 9: return 1 / x;
        case 10: return 1 / (x * x);
    }
}

void generate(int* start_x, int* end_x, int* step_x, int* function)
{
    printf("\tX\t|\tY\t\n");
    printf("-------------------\n");

    for (int i = *start_x; i < *end_x; i += *step_x)
    {
        printf("\t%d\t|\t%lf\t\n", i, calculate((double)i, function));
    }
}

int main(int argc, char** argv)
{
    int start_x, end_x, step_x, function;

    get_input(&start_x, &end_x, &step_x, &function);
    generate(&start_x, &end_x, &step_x, &function);
    return 0;
}


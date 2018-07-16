#include <string.h>
#include <stdlib.h>

int process(int *curr_index, int last_index, char *argv[])
{
    if (*curr_index > last_index) return 1;

    if (strlen(argv[*curr_index]) == 1 && *(argv[*curr_index]) == '+')
    {
        (*curr_index) ++;
        int operand1 = process(curr_index, last_index, argv);
        (*curr_index) ++;
        int operand2 = process(curr_index, last_index, argv);

        return operand1 + operand2;
    }
    else if (strlen(argv[*curr_index]) == 1 && *(argv[*curr_index]) == '-')
    {
        (*curr_index) ++;
        int operand1 = process(curr_index, last_index, argv);
        (*curr_index) ++;
        int operand2 = process(curr_index, last_index, argv);

        return operand1 - operand2;
    }
    else if (strlen(argv[*curr_index]) == 1 && *(argv[*curr_index]) == '*')
    {
        (*curr_index) ++;
        int operand1 = process(curr_index, last_index, argv);
        (*curr_index) ++;
        int operand2 = process(curr_index, last_index, argv);

        return operand1 * operand2;
    }
    else if (strlen(argv[*curr_index]) == 1 && *(argv[*curr_index]) == '/')
    {
        (*curr_index) ++;
        int operand1 = process(curr_index, last_index, argv);
        (*curr_index) ++;
        int operand2 = process(curr_index, last_index, argv);

        return operand1 / operand2;
    }
    else
    {
        int result = atoi(argv[*(curr_index)++]);
        return result;
    }
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1024



// --------------------------------- PREFIX STUFF ------------------------------------- //
#define LIMIT 500
 
typedef struct prefix_expression
{
      int top;
      int stack[LIMIT];
}stack_structure;
 
void initialize(stack_structure *temp)
{
      temp->top = -1;
}
 
void push(stack_structure *temp, int num)
{
      if(temp->top == LIMIT)
      {
            printf("\nStack Overflow\n");
            exit(-1);
      }
      else
      {
            temp->top++;
            temp->stack[temp->top]=num;
      }
}
 
int pop(stack_structure *temp)
{
      int num;
      if(temp->top < 0)
      {
            printf("\nStack Underflow\n");
            exit(-1);
      }
      num = temp->stack[temp->top];
      temp->top--;
      return num;
}
 
int top(stack_structure *temp)
{
      return temp->stack[0];
}
 
void evaluate_prefix(stack_structure *temp, char operator, int x, int y)
{
      int result;
      switch(operator)
      {
            case '-': result = x - y;
                      break;
            case '*': result = x * y;
                      break;
            case '%': result = x % y;
                      break;
            case '/': result = x / y;
                      break;
            case '+': result = x + y;
                      break;
            case '$': result = pow(x, y);
                      break;
      }
      push(temp, result);
}
 
int find_operator(char ch)
{
      switch(ch)
      {
            case '%': return 20;
            case '/': return 20; 
            case '*': return 20;
            case '-': return 20;
            case '$': return 20;
            case '+': return 20;
            default : return 10;
      }
}
 





// --------------- MAIN STUFF ------------------ //


int main(int argc, char** argv)
{
    char buffer[BUFFER_SIZE];
    pid_t child_pid;
    int p1[2], p2[2];

    // no zombies
    signal(SIGCHLD, SIG_IGN);


    // check the pipes are ok
    if (pipe(p1) != 0)
    {
        perror("p1 error");
        exit(1);
    }
    if (pipe(p2) != 0)
    {
        perror("p2 error");
        exit(1);
    }


    // +++++++++++++ FORK ++++++++++++ //
    if ((child_pid = fork()) == 0)
    {
        int x, y, element, length, count, result;
        stack_structure expression_stack;
        initialize(&expression_stack);
        char output[BUFFER_SIZE];

        while (1)
        {
            close(p1[1]);
            close(p2[0]);

            if (read(p1[0], buffer, BUFFER_SIZE) == -1)
            {
                perror("read() error in parent");
                exit(1);
            }
            else
            {
                // ============= PREFIX =========== //
                length = strlen(buffer);

                for(count = length - 1; count >= 0; count--)
                {
                    if(buffer[count] == '\0' || buffer[count] == ' ')
                    {
                        continue;
                    }
                    switch(find_operator(buffer[count]))
                    {
                        case 20 :   x = pop(&expression_stack);
                                    y = pop(&expression_stack);
                                    evaluate_prefix(&expression_stack, buffer[count], x, y);
                                    break;
                        case 10 : element = buffer[count] - '0';
                                    push(&expression_stack, element);
                                    break;
                    }
                }

                result = top(&expression_stack);


                sprintf(output, "Result: %d", result);
                printf("CHILD CALCULATED: [%d]\n", result);

                // ==================================== //

                if (write(p2[1], output, sizeof(output) + 1) == -1)
                {
                    perror("write() error in child");
                    exit(1);
                }
            }
        }

        exit(0);
    }
    else
    {
        while (1)
        {
            close(p1[0]);
            close(p2[1]);

            printf("Expression: ");

            fgets(buffer, BUFFER_SIZE, stdin);

            // printf("Parenting writing to pipe1\n");
            if (write(p1[1], buffer, strlen(buffer) + 1) == -1)
            {
                perror("write() error in parent");
                exit(1);
            }
            else if (read(p2[0], buffer, BUFFER_SIZE) == -1)
            {
                perror("read() error in parent");
                exit(1);
            }
            else
            {
                printf("Result: %s\n", buffer);
            }
        }
    }

    return 0;
}
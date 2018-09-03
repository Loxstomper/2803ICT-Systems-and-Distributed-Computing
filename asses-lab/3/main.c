#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
 

int isOperand(char c)
{
    // If the character is a digit then it must
    // be an operand
    return isdigit(c);
}

int evaluatePrefix(char* exprsn)
{
    // printf("EVALUATING THE PREFIX\n\n");
    stack_structure Stack;
    initialize(&Stack);
 
    for (int j = strlen(exprsn) - 1; j >= 0; j--) 
    {
 
        // Push operand to Stack
        // To convert exprsn[j] to digit subtract
        // '0' from exprsn[j].
        if (isOperand(exprsn[j])) 
        {
            push(&Stack, exprsn[j] - '0');
        }

        else 
        {
            // Operator encountered
            // Pop two elements from Stack
            int o1 = pop(&Stack);
            int o2 = pop(&Stack);
 
            // Use switch case to operate on o1 
            // and o2 and perform o1 O o2.
            switch (exprsn[j]) 
            {
                case '+':
                    push(&Stack, o1 + o2);
                    break;
                case '-':
                    push(&Stack, o1 - o2);
                    break;
                case '*':
                    push(&Stack, o1 * o2);
                    break;
                case '/':
                    push(&Stack, o1 / o2);
                    break;
            }
        }
    }
    
    // printf("TOP OF STACK: [%d]\n", top(&Stack));
    return top(&Stack);
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
        char output[BUFFER_SIZE];
        int result;


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
                // printf("I, the child read [%s]\n", buffer);
                result = evaluatePrefix(buffer);
                // printf("I, the child calculated: [%d]\n", result);

                memset(output, '\0', strlen(output));
                sprintf(output, "%d", result);

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
        // get the UI nice
        printf("\n");

        while (1)
        {
            close(p1[0]);
            close(p2[1]);

            printf("Expression: ");

            fgets(buffer, BUFFER_SIZE, stdin);
            // fgets adds new line char
            buffer[strlen(buffer) - 1] = '\0';

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
                printf("Result    : %s\n\n", buffer);
            }
        }
    }

    return 0;
}
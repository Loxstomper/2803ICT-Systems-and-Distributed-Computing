#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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
    int result;
    char first_char = 'l';

    key_t key = ftok("shmfile",65);
 
    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    char* buffer;
 
    while (1)
    {
        // shmat to attach to shared memory
        buffer = (char*) shmat(shmid,(void*)0,0);

        // printf("READ: %s\n", buffer);
    
        // wait until first character is an operator
        while (isOperand(buffer[0]))
        {

        }

        // printf("READ: %s\n", buffer);

        // printf("Data read from memory: %s\n",buffer);
        
        printf("Got new expression: %s\n", buffer);
        result = evaluatePrefix(buffer);
        printf("Result: %d\n\n", result);

        // write to the memory
        sprintf(buffer, "%d", result);
        first_char = buffer[0];

        //detach from shared memory 
        shmdt(buffer);
    
        // destroy the shared memory
        // shmctl(shmid,IPC_RMID,NULL);
    
    }

    return 0;
}
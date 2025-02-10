#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../stack/stack.h"

bool is_operator(char c);
float compute(float a, float b, char operator);

int main()
{
    char str[1000];
    printf("Enter RPN: ");
    scanf(" %999[^\n]", str);

    Stack *stack = newStack();

    for (char *s = strtok(str, " ,"); s != NULL; s = strtok(NULL, " ,"))
    {
        if (!is_operator(s[0]) || (s[0] == '-' && strlen(s) > 1))
            push(stack, atof(s));
        else
        {
            if (size(stack) < 2)
            {
                printf("\nIncorrect Input\n");
                freeStack(stack);
                return 0;
            }
            else
            {
                float a = *top(stack);
                pop(stack);
                float b = *top(stack);
                pop(stack);
                push(stack, compute(b, a, s[0]));
            }
        }
    }

    printf("\nAnser : %f\n", *top(stack));
    freeStack(stack);
}

bool is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

float compute(float a, float b, char operator)
{
    if (operator== '-')
        return (a - b);
    else if (operator== '*')
        return (a * b);
    else if (operator== '/')
    {
        if (b != 0)
            return (a / b);
        else
            printf("Division by zero!\n");
        return 0;
    }
    else
        return (a + b);
}
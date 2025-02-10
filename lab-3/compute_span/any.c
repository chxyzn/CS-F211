#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 1000

// typedef struct Stack Stack;
// Stack *newStack();
// bool push(Stack *stack, float element);
// float *top(Stack *stack);
// bool pop(Stack *stack);
// bool isEmpty(Stack *stack);
// int size(Stack *stack);
// void freeStack(Stack *stack);
void compute_span(int *a, int *span, int n);

int main()
{
    int n;
    printf("Enter Input Array size : ");
    scanf("%d", &n);

    int arr[n];
    int span_arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d ", &arr[i]);
    }

    compute_span(arr, span_arr, n);

    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", span_arr[i]);
    }
    return 0;
}

void compute_span(int *a, int *span, int n)
{
    // Stack *s = newStack();
    // for (int i = 0; i < n; i++)
    // {
    //     while (!isEmpty(s) && *top(s) <= a[i])
    //     {
    //         pop(s);
    //     }
    //     if (isEmpty(s))
    //         span[i] = i + 1;
    //     else
    //         span[i] = (int)*top(s);
    //     push(s, a[i]);
    // }
}

// struct Stack
// {
//     int top;
//     float data[STACK_SIZE];
// };

// Stack *newStack()
// {
//     Stack *s = (Stack *)malloc(sizeof(Stack));
//     if (s != NULL)
//         s->top = -1;
//     return s;
// }

// bool push(Stack *s, float e)
// {
//     if (s->top == STACK_SIZE - 1)
//         return false;
//     s->data[++(s->top)] = e;
//     return true;
// }

// float *top(Stack *stack)
// {
//     if (stack->top == -1)
//         return NULL;
//     return &stack->data[stack->top];
// }

// int size(Stack *stack)
// {
//     return stack->top + 1;
// }

// bool pop(Stack *stack)
// {
//     if (stack->top == -1)
//         return false;
//     stack->top--;
//     return true;
// }

// bool isEmpty(Stack *stack)
// {
//     return stack->top == -1;
// }

// void freeStack(Stack *stack)
// {
//     free(stack);
// }
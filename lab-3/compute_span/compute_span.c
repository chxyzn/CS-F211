#include <stdlib.h>
#include <stdio.h>
#include "../stack/stack.h"

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
        scanf("%d", &arr[i]);
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
    Stack *s = newStack();
    for (int i = 0; i < n; i++)
    {
        while (!isEmpty(s) && a[(int)*top(s)] <= a[i])
        {
            pop(s);
        }
        if (isEmpty(s))
            span[i] = i + 1;
        else
            span[i] = i - (int)*top(s);
        push(s, i);
    }
    free(s);
}
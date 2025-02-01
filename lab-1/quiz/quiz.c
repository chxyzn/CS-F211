#include <stdlib.h>
#include <stdio.h>
#include "set.h"

int main()
{
    char answers[QUESTIONS];
    printf("Enter 10 characters :\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Question %d: (A, B, C, D, N) : ", i + 1);
        scanf(" %c", &answers[i]);
    }

    int score = answer_checker(answers);
    printf("Score: %d\n", score);
}
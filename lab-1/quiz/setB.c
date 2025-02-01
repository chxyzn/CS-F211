#include "set.h"

int answer_checker(char answers[])
{
    char correct_answers[] = {'B', 'C', 'D', 'A', 'B', 'C', 'D', 'A', 'B', 'C'};
    ;

    int score = 0;
    for (int i = 0; i < QUESTIONS; i++)
    {
        if (answers[i] == correct_answers[i])
            score += 4;
        else if (answers[i] != 'N')
            score--;
    }

    return score >= 0 ? score : 0;
}
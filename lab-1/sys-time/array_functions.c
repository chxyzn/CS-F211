#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array_functions.h"

void read_into_array(FILE *f, Student **students, int *size, int *count)
{
    char temp_name[100];
    float temp_cgpa;
    while (fscanf(f, " %[^\n], %f", temp_name, temp_cgpa) == 2)
    {
        if ((*count) == size - 1)
        {
            *size += *size;
            *students = realloc(*students, sizeof(Student) * (*size));
        }

        (*students)[*count].name = strdup(temp_name);
        (*students)[*count].cgpa = temp_cgpa;
        (*count)++;
    }
}

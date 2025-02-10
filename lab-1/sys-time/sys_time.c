#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "array_functions.h"
#include "context.h"

int main()
{
    struct timeval t1, t2;
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
        return 1;

    char *temp_name;
    float temp_cgpa;
    Student *students = malloc(sizeof(Student) * 5);
    int count = 0, size = 5;

    gettimeofday(&t1, NULL);
    read_into_array(f, &students, &size, &count);
    // while (fscanf(f, "%s, %f", temp_name, temp_cgpa) == 2)
    // {
    //     if (count == size - 1)
    //     {
    //         size += size;
    //         students = realloc(students, sizeof(Student) * size);
    //     }
    //     Student s;
    //     s.name = temp_name;
    //     s.cgpa = temp_cgpa;
    //     students[count] = s;
    //     count++;
    // }
    gettimeofday(&t2, NULL);

    double time = ((t2.tv_sec - t1.tv_sec) * 1e6 + t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("%f", time);
    printf("\n %s %f", students[2].name, students[2].cgpa);
}
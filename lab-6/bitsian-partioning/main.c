#include <stdio.h>
#include <stdlib.h>

typedef struct bitsian
{
    char name[20];
    char rollno[15];
} bitsian;

int main()
{
    FILE *f = fopen("bitsians.txt", "r");
    if (!f)
    {
        return 1;
    }

    char buffer[50];
    if (!fgets(buffer, sizeof(buffer), f))
    {
        return 1;
    }

    int size;
    if (fscanf(f, "%d", &size) != 1)
    {
        return 1;
    }

    bitsian *b = malloc(size * sizeof(bitsian));

    for (int i = 0; i < size; i++)
    {
        if (fscanf(f, "%14[^,],%19[^\n]\n", b[i].rollno, b[i].name) != 2)
        {
            printf("Error reading line %d\n", i + 1);
            free(b);
            fclose(f);
            return 1;
        }
    }

    for (int i = 0; i < size; i++)
    {
        printf("%s, %s\n", b[i].rollno, b[i].name);
    }

    free(b);
    fclose(f);
    return 0;
}

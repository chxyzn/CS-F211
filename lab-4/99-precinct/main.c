#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    ARSON,
    ASSAULT,
    BURGLARY,
    CRIMINAL_MISCHIEF,
    GRAND_LARCENY,
    GRAND_THEFT_AUTO,
    HOMICIDE,
    BREAKING_AND_ENTERING,
    ROBBERY
} CrimeType;

typedef struct criminal
{
    char name[100];
    int age;
    int id;
    int crime_count[9];
    int criminality;
} Criminal;

typedef struct crime
{
    CrimeType type;
    int year;
    int id;
} Crime;

void set_criminal(Criminal *c, char name[], int age, int id);
CrimeType string_to_crimetype(const char *str);
void read_criminals(FILE *f, Criminal *criminals, int size);
void set_crimes(Crime *c, char name[], int year, int id);
void read_crimes(FILE *f, Crime *crimes, int size);
int get_crime_coefficient(CrimeType ct);
void print_criminals(Criminal *c, int size);
void sort_criminals(Criminal *c, int size);
void swap_criminals(Criminal *c, int i, int j);
int get_criminal(Criminal *c, int size, int id);

int main()
{
    FILE *f = fopen("criminal_database.txt", "r");

    int size;
    fscanf(f, "%d\n", &size);
    Criminal criminals[size];
    read_criminals(f, criminals, size);
    int criminal_size = size;
    fclose(f);

    f = fopen("crimes.txt", "r");
    fscanf(f, "%d\n", &size);
    Crime crimes[size];
    read_crimes(f, crimes, size);
    fclose(f);

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        count++;
        CrimeType ct = crimes[i].type;
        // int index = crimes[i].id % 100;
        int index = get_criminal(criminals, criminal_size, crimes[i].id);
        criminals[index].crime_count[ct]++;

        if (crimes[i].id == 125)
        {
            printf("yes %d\n", i);
        }

        int age = crimes[i].year - (2023 - criminals[index].age);
        if (age <= 18)
            criminals[index].criminality += 0.5 * get_crime_coefficient(ct);
        else
            criminals[index].criminality += get_crime_coefficient(ct);
    }

    sort_criminals(criminals, criminal_size);
    print_criminals(criminals, criminal_size);

    f = fopen("out.txt", "w");
    for (int i = 0; i < criminal_size; i++)
    {
        fprintf(f, "%d,%s,%d,%d\n", criminals[i].id, criminals[i].name, criminals[i].age, criminals[i].criminality);
    }
}

int get_criminal(Criminal *c, int size, int id)
{
    int idx = -1;
    for (int i = 0; i < size; i++)
    {
        if (c[i].id == id)
            return i;
    }

    return idx;
}

void sort_criminals(Criminal *c, int size)
{
    for (int i = 1; i < size; i++)
    {
        int k = i;
        while (k > 0 && c[k].criminality > c[k - 1].criminality)
        {
            swap_criminals(c, k, k - 1);
            k--;
        }
    }
}

void swap_criminals(Criminal *c, int i, int j)
{
    Criminal temp = c[i];
    c[i] = c[j];
    c[j] = temp;
}

void print_criminals(Criminal *c, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s ", c[i].name);
        printf("%d ", c[i].age);
        printf("%d ", c[i].id);
        printf("Criminality Score: %d ", c[i].criminality);

        for (int j = 0; j < 9; j++)
        {
            printf("%d ", c[i].crime_count[j]);
        }
        printf("\n");
    }
}

void read_crimes(FILE *f, Crime *crimes, int size)
{
    char s[50];
    int year;
    int id;
    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%99[^,],%d,%d\n", s, &year, &id);
        set_crimes(&crimes[i], s, year, id);
    }
}

void read_criminals(FILE *f, Criminal *criminals, int size)
{
    char s[50];
    int year;
    int id;
    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%99[^,],%d,%d\n", s, &year, &id);
        set_criminal(&criminals[i], s, year, id);
    }
}

void set_crimes(Crime *c, char name[], int year, int id)
{
    c->type = string_to_crimetype(name);
    c->id = id;
    c->year = year;
}

void set_criminal(Criminal *c, char name[], int age, int id)
{
    strcpy(c->name, name);
    int len = strlen(c->name);

    c->age = age;
    c->id = id;
    c->criminality = 0;

    for (int i = 0; i < 9; i++)
    {
        c->crime_count[i] = 0;
    }
}

CrimeType string_to_crimetype(const char *str)
{
    if (strcmp(str, "ARSON") == 0)
        return ARSON;
    if (strcmp(str, "ASSAULT") == 0)
        return ASSAULT;
    if (strcmp(str, "BURGLARY") == 0)
        return BURGLARY;
    if (strcmp(str, "CRIMINAL MISCHIEF") == 0)
        return CRIMINAL_MISCHIEF;
    if (strcmp(str, "GRAND LARCENY") == 0)
        return GRAND_LARCENY;
    if (strcmp(str, "GRAND THEFT AUTO") == 0)
        return GRAND_THEFT_AUTO;
    if (strcmp(str, "HOMICIDE") == 0)
        return HOMICIDE;
    if (strcmp(str, "BREAKING AND ENTERING") == 0)
        return BREAKING_AND_ENTERING;
    else
        return ROBBERY;
}

int get_crime_coefficient(CrimeType ct)
{
    switch (ct)
    {
    case ARSON:
        return 10;
    case ASSAULT:
        return 5;
    case BURGLARY:
        return 5;
    case CRIMINAL_MISCHIEF:
        return 5;
    case GRAND_LARCENY:
        return 10;
    case GRAND_THEFT_AUTO:
        return 10;
    case HOMICIDE:
        return 20;
    case BREAKING_AND_ENTERING:
        return 5;
    case ROBBERY:
        return 10;
    default:
        return 0;
    }
}

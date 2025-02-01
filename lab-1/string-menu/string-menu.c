#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addStringToEnd(char ***a, int *len);
void addStringToBegin(char ***a, int *len);
void deletedAtIndex(char ***a, int index, int *len);
void displayAllElements(char **a, int *len);
char *getString();

int main()
{
    int array_len;
    printf("Specify the Initial Lenght of the Array : ");
    scanf("%d", &array_len);

    char **array = malloc(array_len * sizeof(*array));
    for (int i = 0; i < array_len; i++)
    {
        array[i] = malloc(255);
        scanf("%254s", array[i]);
    }

    int on = 1;
    while (on)
    {
        printf("\nMenu:\n");
        printf("(a) Add a string to the end of the array\n");
        printf("(b) Add a string to the beginning of the array\n");
        printf("(c) Delete the element at index 'x' of the array\n");
        printf("(d) Display the length of the array\n");
        printf("(e) Display all the elements of the array in sequence\n");
        printf("(f) Close\n");
        printf("Select an option: ");

        char choice;
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'a':
            addStringToEnd(&array, &array_len);
            break;

        case 'b':
            addStringToBegin(&array, &array_len);
            break;

        case 'c':
            printf("\nEnter Index : ");
            int d;
            scanf("%d", &d);
            deletedAtIndex(&array, d, &array_len);
            break;

        case 'd':
            printf("\n%d", array_len);
            break;

        case 'e':
            displayAllElements(array, &array_len);
            break;

        case 'f':
            on = 0;
            break;

        default:
            printf("Invalid option! Please try again.\n");
            break;
        }
    }
}

char *getString()
{
    char *s = malloc(255);
    printf("\nEnter your String : ");
    scanf("%s", s);
    return s;
}

void addStringToEnd(char ***a, int *len)
{
    char *str = getString();

    *a = realloc(*a, sizeof(char *) * ((*len) + 1));
    if (*a == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    (*a)[*len] = malloc(255);
    strcpy((*a)[*len], str);
    (*len)++;
}

void addStringToBegin(char ***a, int *len)
{
    char *str = getString();

    *a = realloc(*a, sizeof(char *) * ((*len) + 1));
    if (*a == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    (*len)++;

    for (int i = *len - 1; i > 0; i--)
    {
        (*a)[i] = (*a)[i - 1];
    }

    (*a)[0] = malloc(255);
    if ((*a)[0] == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy((*a)[0], str);
}

void deletedAtIndex(char ***a, int index, int *len)
{
    for (int i = index; i < *len - 1; i++)
    {
        (*a)[i] = (*a)[i + 1];
    }

    *a = realloc(*a, sizeof(char *) * ((*len) - 1));
    if (*a == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    (*len)--;
}

void displayAllElements(char **a, int *len)
{
    for (int i = 0; i < (*len); i++)
    {
        printf("%s\t", a[i]);
    }
}

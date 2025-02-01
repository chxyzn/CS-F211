#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int main()
{
    FILE *file = fopen("LOTR.txt", "r");
    if (file == NULL)
        return 1;
    char *str = malloc(SIZE);
    char *s = malloc(SIZE);

    printf("Enter the word to search : ");
    scanf("%255s", s);

    int count = 0;
    int len = strlen(s);
    while (fgets(str, SIZE, file))
    {
        char *ptr = str;
        ptr = strstr(ptr, s);
        while (ptr != NULL)
        {
            count++;
            ptr += len;
            ptr = strstr(ptr, s);
        }
        // int sttrlen = strlen(str);
        // for (int i = 0; i < sttrlen - len; i++)
        // {
        //     if (str[i] == s[0])
        //     {
        //         int yes = 1;
        //         for (int j = 1; j < len; j++)
        //         {
        //             if (str[i + j] != s[j])
        //             {
        //                 yes = 0;
        //                 break;
        //             }
        //         }
        //         if (yes)
        //             count++;
        //     }
        // }
    }

    printf("\nThe count is %d\n", count);

    free(str);
    free(s);
    fclose(file);
    return 0;
}
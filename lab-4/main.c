#include <stdio.h>

int main()
{
    FILE *f = fopen("data.csv", "r");

    char name[100];
    int height;
    for (int i = 0; i < 10; i++)
    {
        int x = fscanf(f, "%d", name, &height);
        printf("%d %d\n", height, x);
    }
}
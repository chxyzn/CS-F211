#include <stdio.h>
#include <stdlib.h>

#define CHUNK 100000

void merge_sort(int *a, int l, int r);
void merge(int *a, int l, int mid, int r);
int *read_file(FILE *f);
void write_to_file(int *a, int i);
void sort_all();
int find_min_index(int *a, int *valid);

int main()
{
    FILE *f = fopen("dat1000000.csv", "r");
    for (int i = 0; i < 10; i++)
    {
        int *a = read_file(f);
        merge_sort(a, 0, CHUNK - 1);
        write_to_file(a, i);
        free(a);
    }
    fclose(f);

    f = fopen("out.txt", "w");
    sort_all();

    return 0;
}
void sort_all()
{
    FILE **files = malloc(10 * sizeof(FILE *));
    int *a = malloc(10 * sizeof(int));
    int valid[10];

    for (int i = 0; i < 10; i++)
    {
        valid[i] = 0; // Explicitly initialize
        char name[19];
        sprintf(name, "out%d.txt", i);
        files[i] = fopen(name, "r");

        if (files[i] && fscanf(files[i], "%d", &a[i]) == 1)
            valid[i] = 1;
    }

    FILE *out = fopen("out.txt", "w");
    if (!out)
    {
        printf("Error opening out.txt\n");
        return;
    }

    while (1)
    {
        int min = find_min_index(a, valid);
        if (min == -1)
            break;

        fprintf(out, "%d\n", a[min]);

        if (fscanf(files[min], "%d", &a[min]) != 1)
            valid[min] = 0;
    }

    fclose(out);
    for (int i = 0; i < 10; i++)
    {
        if (files[i])
            fclose(files[i]);
    }
    free(files); // Free allocated memory
    free(a);
}

int find_min_index(int *a, int *valid)
{
    int min = __INT_MAX__;
    int min_index = -1;

    for (int i = 0; i < 10; i++)
    {
        if (valid[i] && a[i] < min)
        {
            min = a[i];
            min_index = i;
        }
    }
    return min_index;
}

int *read_file(FILE *f)
{
    int *a = malloc(CHUNK * sizeof(int));
    int height;
    char name[100];
    for (int i = 0; i < CHUNK; i++)
    {
        fscanf(f, "%*d,%99[^,],%*d,%*d,%d", name, &height);
        a[i] = height;
    }

    return a;
}

void write_to_file(int *a, int i)
{
    char name[19];
    sprintf(name, "out%d.txt", i);
    FILE *f = fopen(name, "w");
    if (f == NULL)
        return;

    for (int i = 0; i < CHUNK; i++)
    {
        fprintf(f, "%d\n", a[i]);
    }
    fclose(f);
}

void merge_sort(int *a, int l, int r)
{
    if (r - l < 1)
        return;

    int mid = (l + r) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    merge(a, l, mid, r);
}

void merge(int *a, int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

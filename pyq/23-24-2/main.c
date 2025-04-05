#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

typedef struct lnode
{
    node *head;
    struct lnode *next;
} lnode;

typedef struct list
{
    lnode *head;
    int count;
} list;

typedef struct data
{
    int val;
    int freq;
} data;

list *new_list();
lnode *new_lnode(node *n);
node *new_node(int val);
node *insert_node(node *head, int val);
void insert_lnode(list *l, node *head);
void print_list(list *list);
void set_data(data *d, list *l);
void heapify_data(data *d);
void max_heapify(data *d, int i);
void represent_data(list *l, data *d);
void get_max(data *d);

int main()
{
    FILE *f = fopen("dat.txt", "r");
    list *l = new_list();
    char buff[1000];

    while (fgets(buff, 999, f))
    {
        node *head = NULL;
        for (char *token = strtok(buff, " "); token; token = strtok(NULL, " "))
        {
            head = insert_node(head, atoi(token));
        }
        insert_lnode(l, head);
    }

    data d[100];
    represent_data(l, d);
    get_max(d);
}

list *new_list()
{
    list *l = malloc(sizeof(list));
    l->count = 0;
    l->head = NULL;
    return l;
}

lnode *new_lnode(node *n)
{
    lnode *ln = malloc(sizeof(lnode));
    ln->head = n;
    ln->next = NULL;
    return ln;
}

node *new_node(int val)
{
    node *n = malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    return n;
}

node *insert_node(node *head, int val)
{
    if (!head)
    {
        head = new_node(val);
        return head;
    }

    node *curr = head;
    while (curr->next)
        curr = curr->next;

    curr->next = new_node(val);

    return head;
}

void insert_lnode(list *l, node *head)
{
    if (!l->head)
    {
        l->head = new_lnode(head);
        l->count++;
        return;
    }

    lnode *curr = l->head;
    while (curr->next)
        curr = curr->next;

    curr->next = new_lnode(head);
    l->count++;
    return;
}

void print_list(list *list)
{
    if (!list->head)
        return;

    lnode *curr = list->head;
    while (curr)
    {
        node *n = curr->head;
        while (n)
        {
            printf("%d -> ", n->val);
            n = n->next;
        }

        printf("END");
        printf("\n|\n");
        curr = curr->next;
    }
}

void set_data(data *d, list *l)
{
    for (int i = 0; i < 100; i++)
    {
        d[i].val = i + 1;
        d[i].freq = 0;
    }

    if (!l->head)
        return;

    lnode *curr = l->head;
    while (curr)
    {
        node *n = curr->head;
        while (n)
        {
            int i = n->val;
            d[i - 1].freq++;
            n = n->next;
        }
        curr = curr->next;
    }
}

void max_heapify(data *d, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    int largest = i;
    if (l < 100 && d[l].freq > d[i].freq)
        largest = l;
    if (r < 100 && d[r].freq > d[largest].freq)
        largest = r;

    if (largest != i)
    {
        data temp = d[largest];
        d[largest] = d[i];
        d[i] = temp;

        max_heapify(d, largest);
    }
}

void heapify_data(data *d)
{
    for (int i = (100 / 2) - 1; i >= 0; i--)
        max_heapify(d, i);
}

void represent_data(list *l, data *d)
{
    set_data(d, l);
    heapify_data(d);
}

void get_max(data *d)
{
    printf("Max sold is %d\n", d[0].val);
}
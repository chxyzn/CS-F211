#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node Node;
typedef struct List
{
    int count;
    Node *head;
} List;

typedef struct Node
{
    int digit;
    Node *next;
} Node;

List *new_list();
Node *get_node(char c);
void free_list(List *l);
void add_to_list(List *list, Node *n);
void add(List *l1, List *l2);
void print_list(Node *n);

int main()
{
    char *a = malloc(100), *b = malloc(100);
    printf("Enter the two numbers :\n");
    scanf("%s", a);
    scanf("%s", b);

    List *alist = new_list(), *blist = new_list();

    for (int i = 0; i < strlen(a); i++)
    {
        add_to_list(alist, get_node(a[i]));
    }
    for (int i = 0; i < strlen(b); i++)
    {
        add_to_list(blist, get_node(b[i]));
    }

    add(alist, blist);
    print_list(alist->head);
    free_list(alist);
    free_list(blist);
}

List *new_list()
{
    List *list = (List *)malloc(sizeof(List));
    list->count = 0;
    list->head = NULL;
    return list;
}

Node *get_node(char c)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->digit = c - '0';
    n->next = NULL;
    return n;
}

void free_list(List *l)
{
    if (!l->count)
    {
        free(l);
        return;
    }

    Node *curr = l->head;
    Node *temp;
    while (curr->next != NULL)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(l);
}

void add_to_list(List *list, Node *n)
{
    if (!list->count)
    {
        list->head = n;
        list->count++;
        return;
    }

    Node *head = list->head;
    list->head = n;
    n->next = head;
    list->count++;
}

void add(List *a, List *b)
{
    List *l1, *l2;

    if (a->count < b->count)
        l1 = b, l2 = a;
    else
        l1 = a, l2 = b;

    if (!l1->count || !l1->count)
        return;

    if (l2->count > l1->count)
    {
        List *temp = l1;
        l1 = l2;
        l2 = temp;
    }

    Node *n1 = l1->head;
    Node *n2 = l2->head;

    int carry = 0;
    while (n2 != NULL)
    {
        int sum = n1->digit + n2->digit + carry;
        n1->digit = (sum) % 10;
        carry = sum / 10;

        n2 = n2->next;
        n1 = n1->next;
    }

    Node *prev = l1->head;
    while (prev->next != NULL)
        prev = prev->next;

    while (carry)
    {
        if (n1 == NULL)
        {
            n1 = (Node *)malloc(sizeof(Node));
            n1->digit = carry;
            n1->next = NULL;

            prev->next = n1;
            break;
        }

        int sum = n1->digit + carry;
        n1->digit = sum % 10;
        carry = sum / 10;
        prev = n1;
        n1 = n1->next;
    }
}

void print_list(Node *n)
{
    if (n == NULL)
    {
        printf("\n");
        return;
    }

    print_list(n->next);
    printf("%d", n->digit);
}

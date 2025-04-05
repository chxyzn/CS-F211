#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct llnode
{
    int value;
    struct llnode *next;
} llnode;

typedef struct ll
{
    struct llnode *head;
    int count;
} ll;

typedef struct bstnode
{
    ll *list;
    struct bstnode *left;
    struct bstnode *right;
    struct bstnode *parent;
} bstnode;

typedef struct bst
{
    bstnode *root;
} bst;

ll *new_ll();
llnode *new_node(int val);
void ll_insert(ll *ll, int val);
llnode *insertion_sort(llnode *n);
void print_ll(ll *ll);
bstnode *new_bstnode(ll *l);
bst *new_bst();
void insert_bst(bst *b, ll *l);
void readData(FILE *f, bst *b);
void sortLists(bstnode *n);
void traverse(FILE *f, bstnode *n);

int main()
{
    FILE *f = fopen("numbers_10.txt", "r");
    bst *b = new_bst();
    readData(f, b);
    fclose(f);
    sortLists(b->root);
    f = fopen("out.txt", "w");
    traverse(f, b->root);
    fclose(f);
}

void readData(FILE *f, bst *b)
{
    int size;
    fscanf(f, "%d\n", &size);

    char buff[1000];
    char delim[] = {' ', 13, 10, '\0'};
    for (int i = 0; i < size; i++)
    {
        ll *l = new_ll();
        fgets(buff, 999, f);

        for (char *token = strtok(buff, delim); token; token = strtok(NULL, delim))
        {
            int num = atoi(token);
            // printf(" %s-%d\n", token, (token[0]));
            ll_insert(l, num);
        }
        insert_bst(b, l);
    }
}

void sortLists(bstnode *n)
{
    if (!n)
        return;

    n->list->head->next = insertion_sort(n->list->head->next);
    sortLists(n->left);
    sortLists(n->right);
}

void traverse(FILE *f, bstnode *n)
{
    if (!n)
        return;

    traverse(f, n->left);
    llnode *lln = n->list->head;
    while (lln)
    {
        fprintf(f, "%d ", lln->value);
        lln = lln->next;
    }
    fprintf(f, "\n");
    traverse(f, n->right);
}

ll *new_ll()
{
    ll *ll = malloc(sizeof(ll));
    ll->head = NULL;
    ll->count = 0;
    return ll;
}

llnode *new_node(int val)
{
    llnode *node = malloc(sizeof(llnode));
    node->value = val;
    node->next = NULL;
    return node;
}

void ll_insert(ll *ll, int val)
{
    llnode *n = new_node(val);
    if (!ll->head)
    {
        ll->head = n;
        ll->count++;
        return;
    }

    llnode *curr = ll->head;
    while (curr->next)
    {
        curr = curr->next;
    }
    curr->next = n;
    ll->count++;
    return;
}

llnode *insertion_sort(llnode *n)
{
    if (!n || !n->next)
        return n;

    llnode *sorted = NULL;
    llnode *current = n;

    while (current)
    {
        llnode *next = current->next;

        if (!sorted || current->value < sorted->value)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            llnode *temp = sorted;
            while (temp->next && temp->next->value < current->value)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    return sorted;
}

void print_ll(ll *ll)
{
    if (!ll)
    {
        printf("Linked list is NULL.\n");
        return;
    }
    if (!ll->head)
    {
        printf("Linked list is empty.\n");
        return;
    }

    llnode *current = ll->head;
    printf("Linked list (count: %d): ", ll->count);
    while (current != NULL)
    {
        printf("%d", current->value);
        if (current->next != NULL)
        {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

bst *new_bst()
{
    bst *b = malloc(sizeof(bst));
    b->root = NULL;
    return b;
}

bstnode *new_bstnode(ll *l)
{
    bstnode *bn = malloc(sizeof(bstnode));
    bn->list = l;
    bn->right = NULL;
    bn->left = NULL;
    bn->parent = NULL;
    return bn;
}

void insert_bst(bst *b, ll *l)
{
    bstnode *n = new_bstnode(l);
    if (!b->root)
    {
        b->root = n;
        return;
    }

    bstnode *curr = b->root;
    while (curr)
    {
        if (curr->list->head->value >= l->head->value)
        {
            if (!curr->left)
            {
                curr->left = n;
                n->parent = curr;
                return;
            }
            curr = curr->left;
        }
        else
        {
            if (!curr->right)
            {
                curr->right = n;
                n->parent = curr;
                return;
            }
            curr = curr->right;
        }
    }
}
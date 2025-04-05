#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

typedef struct node
{
    struct person *value;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef struct bst
{
    Node *root;
} BST;

BST *new_bst();
Node *new_node(struct person *p);
void insert(BST *bst, struct person *p);
void inorder(Node *n);
Node *search_id(BST *bst, int id);

int main()
{
    FILE *f = fopen("dat10.csv", "r");
    struct person people[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        people[i].name = malloc(sizeof(char) * 100);
    }

    for (int i = 0; i < SIZE; i++)
    {
        fscanf(f, "%d,%[^,],%d,%d,%d\n", &people[i].id, people[i].name, &people[i].age, &people[i].height, &people[i].weight);
    }

    BST *bst = new_bst();
    for (int i = 0; i < SIZE; i++)
    {
        insert(bst, &people[i]);
    }

    // inorder(bst->root);
    render_bst(bst->root);
}

BST *new_bst()
{
    BST *bst = malloc(sizeof(bst));
    bst->root = NULL;
    return bst;
}

Node *new_node(struct person *p)
{
    Node *n = malloc(sizeof(Node));
    n->value = p;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(BST *bst, struct person *p)
{
    if (!bst->root)
    {
        Node *n = new_node(p);
        bst->root = n;
    }
    else
    {
        Node *node = bst->root;
        while (node)
        {
            if (p->height <= node->value->height)
            {
                if (!node->left)
                {
                    Node *n = new_node(p);
                    node->left = n;
                    n->parent = node;
                    return;
                }
                node = node->left;
            }
            else
            {
                if (!node->right)
                {
                    Node *n = new_node(p);
                    node->right = n;
                    n->parent = node;
                    return;
                }
                node = node->right;
            }
        }
    }
}

void inorder(Node *n)
{
    if (!n)
        return;

    inorder(n->left);
    printf("%d ", n->value->height);
    inorder(n->right);
}

Node *search_id(BST *bst, int id)
{
    if (!bst->root)
        return NULL;

    Node *curr = bst->root;

    while (curr)
    {
        if (id < curr->value->id)
            curr = curr->left;
        else if (id > curr->value->id)
            curr = curr->right;
        else
            return curr;
    }

    return curr;
}

Node *least_common_ancestor(BST *bst, int id1, int id2)
{
    if (!bst->root)
        return NULL;

    Node *n1 = search_id(bst, id1);
    Node *n2 = search_id(bst, id2);

    if (!n1 || !n2)
        return NULL;

    while (n1 != n2)
    {
        if (n1->value->id <= n2->value->id)
        {
            if (!n1->parent)
                return n1;
            n1 = n1->parent;
        }
        else
        {
            if (!n1->parent)
                return n1;
            n2 = n2->parent;
        }
    }
}
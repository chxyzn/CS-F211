#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef struct bst
{
    Node *root;
} BST;

BST *new_bst();
Node *new_node(int value);
void bst_insert(Node *root, int value);
void render_bst(Node *root, int space, char branch);
void inorder(Node *node);
void level_traversal(Node *root);
void level_traversal_reverse(Node *root);
int get_max_level(Node *root);
void print_level(Node *root, int level);
int check_bst(Node *root, int min, int max);
Node *remove_half_nodes(Node *root);
Node *flatten(Node *node, Node **flat);
Node *flatten_wrong(Node *node, Node *flat);

int main()
{
    BST *bst = new_bst();
    Node *n = new_node(4);
    bst->root = n;

    int a[] = {2, 6, 1, 3, 5, 7};
    for (int i = 0; i < 6; i++)
    {
        bst_insert(bst->root, a[i]);
    }

    level_traversal(bst->root);
    printf("\n");
    Node *f;

    f = flatten_wrong(bst->root, f);
    // while (f->parent != NULL)
    //     f = f->parent;
    level_traversal(f);
    inorder(f);
}

BST *new_bst()
{
    BST *bst = (BST *)malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = value;
    return node;
}

void bst_insert(Node *root, int value)
{
    if (root == NULL)
    {
        Node *n = new_node(value);
        root = n;
        return;
    }
    if (root->value < value)
    {
        if (root->right == NULL)
        {
            Node *n = new_node(value);
            root->right = n;
            n->parent = root;
            return;
        }
        else
            bst_insert(root->right, value);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *n = new_node(value);
            root->left = n;
            n->parent = root;
            return;
        }
        else
            bst_insert(root->left, value);
    }
}

void inorder(Node *node)
{
    if (node == NULL)
        return;

    inorder(node->left);
    printf("%d ", node->value);
    inorder(node->right);
}

void render_bst(Node *root, int space, char branch)
{
    if (root == NULL)
        return;

    space += 6;

    render_bst(root->right, space, '/');

    printf("\n");
    for (int i = 6; i < space - 2; i++)
        printf(" ");

    if (branch == '/')
        printf("┌── ");
    else if (branch == '\\')
        printf("└── ");

    printf("%d\n", root->value);

    render_bst(root->left, space, '\\');
}

void level_traversal(Node *root)
{
    int l = get_max_level(root);
    for (int i = 1; i <= l; i++)
    {
        print_level(root, i);
        printf("\n");
    }
}

int get_max_level(Node *root)
{
    if (root == NULL)
        return 0;

    int l = get_max_level(root->left);
    int r = get_max_level(root->right);

    return l > r ? l + 1 : r + 1;
}

void print_level(Node *root, int level)
{
    if (root == NULL)
        return;
    else if (level == 1)
        printf("%d ", root->value);
    else
    {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

void level_traversal_reverse(Node *root)
{
    int l = get_max_level(root);
    for (int i = l; i >= 1; i--)
    {
        print_level(root, i);
        printf("\n");
    }
}

int check_bst(Node *root, int min, int max)
{
    if (root == NULL)
        return 1;

    if (root->value < min || root->value > max)
        return 0;

    int l = check_bst(root->left, min, root->value);
    int r = check_bst(root->right, root->value, max);

    return l * r;
}

// you return the same node if the node is not half or you return a child node if the node is half.
Node *remove_half_nodes(Node *root)
{
    if (root == NULL)
        return NULL;

    root->left = remove_half_nodes(root->left);
    root->right = remove_half_nodes(root->right);

    if (root->left == NULL && root->right != NULL)
    {
        Node *newRoot = root->right;
        free(root);
        return newRoot;
    }
    if (root->right == NULL && root->left != NULL)
    {
        Node *newRoot = root->left;
        free(root);
        return newRoot;
    }

    return root;
}

void free_tree(Node *node)
{
    if (node == NULL)
        return;

    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

Node *flatten(Node *node, Node **flat)
{
    if (node == NULL)
        return NULL;

    if (*flat == NULL)
        *flat = new_node(node->value);
    else
    {
        Node *n = new_node(node->value);
        n->parent = *flat;
        (*flat)->right = n;
        *flat = n;
    }

    flatten(node->left, flat);
    flatten(node->right, flat);

    return *flat;
}

Node *flatten_wrong(Node *node, Node *flat)
{
    if (node == NULL)
        return NULL;

    if (flat == NULL)
    {
        flat = new_node(node->value);
    }
    else
    {
        Node *n = new_node(node->value);
        n->parent = flat;
        flat->right = n;
        flat = flat->right;
    }

    flatten_wrong(node->left, flat);
    flatten_wrong(node->right, flat);

    return flat;
}
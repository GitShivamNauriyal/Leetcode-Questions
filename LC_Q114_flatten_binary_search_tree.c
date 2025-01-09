#include <stdio.h>
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flatten(struct TreeNode *root);
void insert(struct TreeNode **root);
struct TreeNode *insert_node(struct TreeNode *root, struct TreeNode *node);
void printTree(struct TreeNode *root);
void freeAll(struct TreeNode *root);

void main()
{
    struct TreeNode *root = NULL;
    int n, i = 1;
    while (i)
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1. Insert a Node.\n");
        printf("2. Print List\n");
        printf("3. Flatten Tree into Linked List\n");
        printf("4. EXIT.\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            insert(&root);
            break;
        case 2:
            printf("Tree: ");
            printTree(root);
            break;
        case 3:
            flatten(root);
            break;
        case 4:
            i = 0;
            freeAll(root);
            printf("Exited");
            break;
        default:
            printf("Enter correct choice");
            break;
        };
    }
}
void flatten(struct TreeNode *root)
{
    if (root == NULL)
        return;
    flatten(root->left);
    flatten(root->right);
    if (root->left == NULL)
        return;
    struct TreeNode *temp = root->left; // last node in the left side needs to be linked with next on right
    while (temp->right != NULL)
        temp = temp->right;
    temp->right = root->right;
    root->right = root->left;
    root->left = NULL;
}

void insert(struct TreeNode **root)
{
    int n;
    struct TreeNode *new_node = NULL;
    new_node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    printf("Enter data for new node: ");
    scanf("%d", &n);
    new_node->val = n;
    new_node->left = NULL;
    new_node->right = NULL;
    *root = insert_node(*root, new_node);
}

struct TreeNode *insert_node(struct TreeNode *root, struct TreeNode *node)
{
    if (root == NULL)
        return node;
    if (root->val > node->val)
        root->left = insert_node(root->left, node);
    else
        root->right = insert_node(root->right, node);

    return root;
}

void printTree(struct TreeNode *root)
{
    if (root == NULL)
        return;
    printTree(root->left);
    printf("-%d- ", root->val);
    printTree(root->right);
}

void freeAll(struct TreeNode *root)
{
    if (root == NULL)
        return;
    freeAll(root->left);
    freeAll(root->right);
    free(root);
}
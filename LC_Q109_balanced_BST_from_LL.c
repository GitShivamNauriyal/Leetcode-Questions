/*
Date:- 30 sep 2024
Project:- Leetcode Problem 109 - Balanced BST from Linked List
Purpose:- Problem Solving Practice
Problem Statement:- Given the head of a singly linked list where
                    elements are sorted in ascending order,
                    convert it to a height-balanced binary search tree.
*/

#include <stdio.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void insertAtEnd(struct ListNode **head);
struct TreeNode *insertInBST(struct TreeNode *, int);
struct TreeNode *newNode(int item);
struct TreeNode *sortedListToBST(struct ListNode *head); // main function used
void printList(struct ListNode *head);
void printTree(struct TreeNode *head);
void freeList(struct ListNode **head);
void freeTree(struct TreeNode **root);

int main(void)
{
    struct ListNode *head = NULL;
    struct TreeNode *root = NULL;
    int n, i = 1;
    while (i)
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1. Insert at end.\n");
        printf("2. Print List\n");
        printf("3. Convert Linked List into Balanced Binary Search Tree\n");
        printf("4. EXIT.\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            insertAtEnd(&head);
            break;
        case 2:
            printList(head);
            break;
        case 3:
            root = sortedListToBST(head);
            printTree(root);
            break;
        case 4:
            i = 0;
            freeList(&head);
            // freeTree(&root);
            printf("Exited");
            break;
        default:
            printf("Enter correct choice");
            break;
        };
    }
}

void insertAtEnd(struct ListNode **head)
{
    int data;
    printf("Enter data: ");
    scanf("%d", &data);

    struct ListNode *new_node = (struct ListNode *)malloc(sizeof(struct ListNode));

    new_node->val = data;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    struct ListNode *current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

void printList(struct ListNode *head)
{
    struct ListNode *current = head;

    printf("\nList: ");
    printf("Head -> ");
    while (current != NULL)
    {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

void printTree(struct TreeNode *root)
{
    if (root == NULL)
        return;
    printf("%d -> ", root->val);
    printTree(root->left);
    printTree(root->right);
}

struct TreeNode *newNode(int item)
{
    struct TreeNode *temp =
        (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->val = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct TreeNode *insertInBST(struct TreeNode *node, int key)
{
    printf("Node: %d\n", key);
    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(key);

    // If the key is already present in the tree,
    // return the node
    if (node->val == key)
        return node;

    // Otherwise, recur down the tree. If the key
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (node->val < key)
        node->right = insertInBST(node->right, key);

    // If the key to be inserted is smaller than
    // the node's key,insert it in the left subtree
    else
        node->left = insertInBST(node->left, key);

    // Return the (unchanged) node pointer
    return node;
}

/******************************function used******************************************** */

struct TreeNode *sortedListToBST(struct ListNode *head)
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL)
    {
        struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        root->val = head->val;
        root->left = root->right = NULL;
        return root;
    }

    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *prev = NULL; // to keep track of the node before slow

    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // Disconnect the left half from the middle
    if (prev != NULL)
        prev->next = NULL;

    // Create the root node with the middle value
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = slow->val;

    // Recursively construct the left subtree from the first half
    root->left = sortedListToBST(head);

    // Recursively construct the right subtree from the second half
    root->right = sortedListToBST(slow->next);

    return root;
}

/****************************************************************************************** */

/*-*-*-*-*-*-*--*-*--*-*-*-*-*-*-***-*-*-**-**-*-*-*-***-*-***-*-*-*-*--*-*-*-*-*-*--*/
//////////////////////////FASTER FUNCTION////////////////////////////////////////////////
/*

// Helper function to count the number of nodes in the linked list
int countNodes(struct ListNode* head) {
    int count = 0;
    struct ListNode* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Recursive function to construct BST
struct TreeNode* sortedListToBSTHelper(struct ListNode** head_ref, int n) {
    // Base case
    if (n <= 0)
        return NULL;

    // Recursively construct the left subtree
    struct TreeNode* left = sortedListToBSTHelper(head_ref, n / 2);

    // Allocate memory for the root, assign the middle value, and move head_ref forward
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = (*head_ref)->val;
    root->left = left;

    // Move the head pointer to the next node
    *head_ref = (*head_ref)->next;

    // Recursively construct the right subtree
    root->right = sortedListToBSTHelper(head_ref, n - n / 2 - 1);

    return root;
}

// Main function to convert sorted list to BST
struct TreeNode* sortedListToBST(struct ListNode* head) {
    int n = countNodes(head); // Count the number of nodes in the list
    return sortedListToBSTHelper(&head, n); // Construct the BST
}
*/

/*-*-*-*-*-*-*--*-*--*-*-*-*-*-*-***-*-*-**-**-*-*-*-***-*-***-*-*-*-*--*-*-*-*-*-*--*/

void freeList(struct ListNode **head)
{
    struct ListNode *temp, *current = *head;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    printf("All List Nodes Freed\n");
}

// incomplete
void freeTree(struct TreeNode **root)
{
    if ((*root == NULL) || ((*root)->left == NULL && (*root)->right == NULL))
    {
        free(root);
        printf("All Tree Nodes Freed");
        return;
    }
    if ((*root)->left == NULL)
        freeTree(&(*root)->right);
    if ((*root)->right == NULL)
        freeTree(&(*root)->left);
}
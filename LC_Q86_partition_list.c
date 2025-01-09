/*
Date:- 29 sep 2024
Project:- LeetCode Problem 86 - Partition List, using elements greater or equal to x.
Purpose:- Problem solving practice
Problem Statement:- Given the head of a linked list and a value x,
                    partition it such that all nodes less than x
                    come before nodes greater than or equal to x
                    You should preserve the original relative order
                    of the nodes in each of the two partitions.
*/

#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

void insertAtEnd(struct ListNode **head);
void printList(struct ListNode *head);
struct ListNode *partition(struct ListNode *head, int x);
void freeAll(struct ListNode **head);
struct ListNode *reverseBetween(struct ListNode *head, int left, int right)
{
    printf("Left = %d, Right = %d\n", left, right);
    if (left == right || head == NULL)
        return head;
    int L = left, R = right;
    struct ListNode *LnodePrev = head, *RnodeNext = NULL, *Lnode = head, *Rnode = head;
    while (--left && Lnode)
    {
        LnodePrev = Lnode;
        Lnode = Lnode->next;
    }
    while (--right && Rnode)
        Rnode = Rnode->next;
    RnodeNext = Rnode->next;
    struct ListNode *prev = RnodeNext, *curr = Lnode, *next = NULL;
    int n = R - L + 1;
    // if (L != 1)
    // prev = RnodeNext;
    while ((n--) && (curr != NULL))
    {
        printf("%d-", curr->val);
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        printf("%d\n", n);
    }
    if (prev->next != NULL)
        printf("prev = %d\n", prev->val);
    if (L != 1)
        LnodePrev->next = prev;
    else
        head = prev;
    struct ListNode *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
    return head;
}

int main(void)
{
    struct ListNode *head = NULL;
    int n, i = 1, x;
    while (i)
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1. Insert at end.\n");
        printf("2. Print List\n");
        printf("3. Partition and bring specific small elements in the beginning\n");
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
            printf("Enter the value of x: ");
            scanf("%d", &x);
            head = partition(head, x);
            printList(head);
            break;
        case 4:
            i = 0;
            freeAll(&head);
            printf("Exited");
            break;
        case 5:
            int x, y;
            printf("Enter:\n");
            scanf("%d %d", &x, &y);
            head = reverseBetween(head, x, y);
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
    int n = 0;
    struct ListNode *current = head;

    printf("\nList: ");
    printf("Head -> ");
    while (current != NULL && n < 20)
    {
        printf("%d -> ", current->val);
        current = current->next;
        n++;
    }
    printf("NULL\n");
}

struct ListNode *partition(struct ListNode *head, int x)
{
    struct ListNode *first = head;
    struct ListNode *current = head;
    struct ListNode *cNode = NULL;
    struct ListNode *cPrev = NULL;
    struct ListNode *prev = NULL;
    struct ListNode *temp = NULL;
    while (current != NULL)
    {
        if (current->val >= x)
        {
            cNode = current;
            break;
        }
        cPrev = current; // if cPrev = NULL, cNode is first Node of the list
        current = current->next;
    }
    if (cNode == NULL)
        return first;
    printf("cNode: %d\n", cNode->val);
    current = cNode->next;
    prev = cNode;
    while (current != NULL)
    {
        printf("current: %d\n", current->val);
        printf("prev: %d\n", current->val);
        temp = current->next;
        if (current->val < x)
        {
            prev->next = current->next;
            current->next = cNode;
            if (cPrev == NULL)
            {
                first = current;
                cPrev = current;
            }
            else
            {
                cPrev->next = current;
                cPrev = current;
            }
            printf("cPrev: %d\n", cPrev->val);
        }
        else
            prev = current;
        current = temp;
    }
    return first;
}

void freeAll(struct ListNode **head)
{
    struct ListNode *temp, *current = *head;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    printf("All Nodes Freed\n");
}

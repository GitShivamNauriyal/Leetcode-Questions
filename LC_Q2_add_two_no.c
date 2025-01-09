/*
Date:- 31 aug 2024
Project:- leatcode problem 2
Purpose:- learning and testing code
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

void insertAtEnd(struct ListNode **head, int data)
{
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

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int sum, carry = 0, total;
    struct ListNode *newList = NULL;
    while (l1 != NULL || l2 != NULL || carry != 0)
    {
        if (l1 != NULL && l2 != NULL)
            sum = l1->val + l2->val;
        else if (l1 != NULL)
            sum = l1->val;
        else if (l2 != NULL)
            sum = l2->val;
        total = sum + carry;
        printf("sum - %d\n", sum);
        printf("TOTAL - %d\n", total);
        sum = 0;
        carry = 0;
        if (total >= 10)
            carry = total / 10;
        insertAtEnd(&newList, total % 10);
        if (l1 != NULL)
            l1 = l1->next;
        if (l2 != NULL)
            l2 = l2->next;
        printf("carry - %d\n", carry);
    }
    return newList;
}

int main(void)
{
    int n;
    struct ListNode *l1 = NULL, *l2 = NULL, *FL = NULL;
    printf("L1=");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &n);
        insertAtEnd(&l1, n);
    }
    printf("L2=");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &n);
        insertAtEnd(&l2, n);
    }
    FL = addTwoNumbers(l1, l2);
    while (FL != NULL)
    {
        printf("%d ", FL->val);
        FL = FL->next;
    }
}
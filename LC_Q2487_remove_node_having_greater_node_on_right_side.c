#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

void insertAtEnd(struct ListNode **head);
void printList(struct ListNode *head);
void freeAll(struct ListNode **head);

/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
struct ListNode *removeNodes(struct ListNode *head);
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/

/*-------------HIPPSTER BULLSHIT METHOD--------------*/
// struct ListNode *reverseList(struct ListNode *head);
// struct ListNode *removeNodes(struct ListNode *head);

int main(void)
{
    struct ListNode *head = NULL;
    int n, i = 1, x;
    while (i)
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1. Insert at end.\n");
        printf("2. Print List\n");
        printf("3. Remove nodes having greater nodes on their right side\n");
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
            head = removeNodes(head);
            printList(head);
            break;
        case 4:
            i = 0;
            freeAll(&head);
            printf("Exited");
            break;
        default:
            printf("Enter correct choice");
            break;
        };
    }
}

/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------COOL GRAND KAI METHOD---------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
// Function to remove nodes based on the problem constraints
struct ListNode *removeNodes(struct ListNode *head)
{
    if (!head)
        return NULL;

    struct ListNode *stack[100000]; // Assume a large enough size for the stack
    int top = -1;

    struct ListNode *current = head;

    // Traverse the list
    while (current)
    {
        // Pop nodes from the stack if their value is less than the current node's value
        while (top >= 0 && stack[top]->val < current->val)
        {
            top--;
        }

        // Push the current node onto the stack
        stack[++top] = current;

        // Move to the next node
        current = current->next;
    }

    // Rebuild the linked list from the stack
    struct ListNode *newHead = stack[0];
    struct ListNode *temp = newHead;

    for (int i = 1; i <= top; i++)
    {
        temp->next = stack[i];
        temp = temp->next;
    }

    // Terminate the list
    temp->next = NULL;

    return newHead;
}

/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*---------------------------------------------------*/
/*-------------HIPPSTER BULLSHIT METHOD--------------*/
/*
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev = NULL, *next = NULL, *current = head;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

struct ListNode* removeNodes(struct ListNode* head) {
    // Step 1: Reverse the list
    head = reverseList(head);

    // Step 2: Remove nodes that don't satisfy the condition
    struct ListNode *current = head, *temp = head;
    int max = head->val;

    while (current != NULL && current->next != NULL) {
        if (current->next->val < max) {
            // Remove the next node
            current->next = current->next->next;
        } else {
            // Update max and move to next node
            max = current->next->val;
            current = current->next;
        }
    }

    // Step 3: Reverse the list back to its original order
    head = reverseList(head);
    return head;
}

*/
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

/*
Date:- 28 Sep 2024
Problem:- leetcode problem 82 - Remove duplicate elements from sorted list
Purpose:- Problem solving practice
Problem statement:- Given the head of a sorted linked list,
                    delete all nodes that have duplicate numbers,
                    leaving only distinct numbers from the original list.
                    Return the linked list sorted as well.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void insertAtEnd(struct Node **head);
void printList(struct Node *head);
struct Node *deleteDuplicates(struct Node *head);
void freeAll(struct Node **head);

void main()
{
    struct Node *head = NULL;
    int n, i = 1;
    while (i)
    {
        printf("\n----------------------------------------------------\n\n");
        printf("1. Insert at end.\n");
        printf("2. Print List\n");
        printf("3. Delete Duplicate Nodes\n");
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
            deleteDuplicates(head);
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

void insertAtEnd(struct Node **head)
{
    int data;
    printf("Enter data: ");
    scanf("%d", &data);

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

void printList(struct Node *head)
{
    struct Node *current = head;

    printf("\nList: ");
    printf("Head -> ");
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

struct Node *deleteDuplicates(struct Node *head)
{
    int buffer, dup = 0;
    struct Node *temp, *prev = NULL, *first = head;
    while (head != NULL)
    {
        if (dup == 1 && head->next == NULL) // when we reach last element
        {
            // printf("Reached last Node, also a duplicate: %d\n", head->data);
            free(head);
            if (prev != NULL)
                prev->next = NULL; // make the last element point to NULL
            else
                first = NULL; // if prev == NULL, that meanns all the elements in the list were same and the list now needs to be empty
            break;
        }
        // printf("Buffer: %d\n", head->data);

        if (head->next != NULL && head->next->data == head->data)
        {
            // printf("Node Found: %d\n", head->next->data);
            temp = head->next;
            head->next = head->next->next; // removing element from the list
            free(temp);
            dup = 1;
        }
        else if (dup == 1)
        {
            // printf("Non dup found, removing previous dup: %d\n", head->data);
            temp = head;
            if (head == first) // if the node to be removed is the first element of the list then first needs to point at the next and since prev still points to NULL to it should not be bothered with
            {
                // printf("Dup is first Node: %d\n", head->data);
                first = head->next;
                // printf("New First: %d\n", first->data);
            }
            else if (prev != NULL)
                prev->next = head->next; // when node to be removed is not first node of the list the the previous node needs to point to the next of the node to be removed to actually remove the node.
            head = head->next;
            free(temp);
            dup = 0;
        }
        else
        {
            prev = head; // when no duplicate is found so we move foreward and prev needs to point at head for backtracking
            // printf("No Duplicate Found, Node: %d\n", head->data);
            head = head->next;
        }
        // head should not point to next in every itiration because if same node is found then it is being removed above and we require the current head to check is there are further more same elements in the list
        // refer to the diagram representation of the algo made below of this function for better understanding of the code
    }
    return first;
}

/*
PICTOREAL ALGO OF THE FUNCTION

Inputed list: Head -> 1 -> 1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 5 -> NULL
head = 1 (first node)
first = 1 (first node)
prev = NULL
dup = 0
Steps:
> [1] - 1 - 1 - 2 - 3 - 3 - 4 - 5 - 5 -_#_  dup = 1     first = 1
> [1] - 1 - 2 - 3 - 3 - 4 - 5 - 5 -_#_      dup = 1     first = 1
> [1] - 2 - 3 - 3 - 4 - 5 - 5 -_#_          dup = 1     first = 1
> [2] - 3 - 3 - 4 - 5 - 5 -_#_              dup = 0     first = 2
   ^--prev
> 2 - [3] - 3 - 4 - 5 - 5 -_#_              dup = 1     first = 2
> 2 - [3] - 4 - 5 - 5 -_#_                  dup = 1     first = 2
> 2 - [4] - 5 - 5 -_#_                      dup = 0     first = 2
       ^--prev
> 2 - 4 - [5] - 5 -_#_                      dup = 1     first = 2
> 2 - 4 - [5] -_#_                          dup = 1     first = 2
> 2 - 4 -_#_                                dup = 0     first = 2
        ^--prev->next = NULL, since dup was 1 and prev->next == NULL
        prev was not NULL therefore list contains node which are not duplicate

*/

void freeAll(struct Node **head)
{
    struct Node *temp, *current = *head;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    printf("All Nodes Freed\n");
}

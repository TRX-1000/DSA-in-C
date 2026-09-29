#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;


// --------------------------------------------------
// INITIALIZE
// --------------------------------------------------

void initList(List *list)
{
    list->head = NULL;
    list->tail = NULL;
}


// --------------------------------------------------
// CREATE NODE
// --------------------------------------------------

Node *createNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    return temp;
}


// --------------------------------------------------
// INSERT AT BEGINNING
// --------------------------------------------------

void insertBeginning(List *list, int data)
{
    Node *temp = createNode(data);

    // Empty list
    if (list->head == NULL)
    {
        list->head = temp;
        list->tail = temp;
    }

    // Non-empty list
    else
    {
        temp->next = list->head;
        list->head->prev = temp;

        list->head = temp;
    }
}


// --------------------------------------------------
// INSERT AT END
// --------------------------------------------------

void insertEnd(List *list, int data)
{
    Node *temp = createNode(data);

    // Empty list
    if (list->tail == NULL)
    {
        list->head = temp;
        list->tail = temp;
    }

    // Non-empty list
    else
    {
        temp->prev = list->tail;
        list->tail->next = temp;

        list->tail = temp;
    }
}


// --------------------------------------------------
// INSERT AT POSITION
// position starts from 1
// --------------------------------------------------

void insertPosition(List *list, int data, int position)
{
    if (position <= 1)
    {
        insertBeginning(list, data);
        return;
    }

    Node *p = list->head;

    // Move to node at position-1
    for (int i = 1; i < position - 1 && p != NULL; i++)
    {
        p = p->next;
    }

    // Invalid position
    if (p == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    // Inserting after tail
    if (p == list->tail)
    {
        insertEnd(list, data);
        return;
    }

    Node *temp = createNode(data);

    // p <-> temp <-> p->next

    temp->next = p->next;
    temp->prev = p;

    p->next->prev = temp;
    p->next = temp;
}


// --------------------------------------------------
// DELETE FROM BEGINNING
// --------------------------------------------------

void deleteBeginning(List *list)
{
    if (list->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *temp = list->head;

    // Only one node
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    else
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(temp);
}


// --------------------------------------------------
// DELETE FROM END
// --------------------------------------------------

void deleteEnd(List *list)
{
    if (list->tail == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *temp = list->tail;

    // Only one node
    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    else
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(temp);
}


// --------------------------------------------------
// DELETE FROM POSITION
// position starts from 1
// --------------------------------------------------

void deletePosition(List *list, int position)
{
    if (list->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (position <= 1)
    {
        deleteBeginning(list);
        return;
    }

    Node *p = list->head;

    // Move p to required node
    for (int i = 1; i < position && p != NULL; i++)
    {
        p = p->next;
    }

    if (p == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    if (p == list->tail)
    {
        deleteEnd(list);
        return;
    }

    // Connect previous and next nodes

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);
}


// --------------------------------------------------
// SEARCH
// --------------------------------------------------

Node *search(List *list, int key)
{
    Node *p = list->head;

    while (p != NULL)
    {
        if (p->data == key)
            return p;

        p = p->next;
    }

    return NULL;
}


// --------------------------------------------------
// DISPLAY FORWARD
// --------------------------------------------------

void displayForward(List *list)
{
    Node *p = list->head;

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}


// --------------------------------------------------
// DISPLAY BACKWARD
// --------------------------------------------------

void displayBackward(List *list)
{
    Node *p = list->tail;

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->prev;
    }

    printf("\n");
}


// --------------------------------------------------
// FREE ENTIRE LIST
// --------------------------------------------------

void freeList(List *list)
{
    Node *p = list->head;

    while (p != NULL)
    {
        Node *next = p->next;

        free(p);

        p = next;
    }

    list->head = NULL;
    list->tail = NULL;
}


// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main()
{
    List list;

    initList(&list);

    insertEnd(&list, 10);
    insertEnd(&list, 20);
    insertEnd(&list, 30);

    insertBeginning(&list, 5);

    insertPosition(&list, 15, 3);

    printf("Forward: ");
    displayForward(&list);

    printf("Backward: ");
    displayBackward(&list);

    deleteBeginning(&list);
    deleteEnd(&list);
    deletePosition(&list, 2);

    printf("After deletion: ");
    displayForward(&list);

    Node *result = search(&list, 20);

    if (result != NULL)
        printf("20 found\n");
    else
        printf("20 not found\n");

    freeList(&list);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct node {
    int data;
    struct node *next;
} node_t;

// List structure
typedef struct list {
    node_t *head;
} list_t;


// Initialize list
void init_list(list_t *list)
{
    // Create the dummy/header node
    list->head = (node_t *)malloc(sizeof(node_t));

    // No actual data nodes yet
    list->head->next = NULL;
}


// Insert in sorted/ascending order
void insert(list_t *list, int data)
{
    // 1. Create new node
    node_t *temp = (node_t *)malloc(sizeof(node_t));

    temp->data = data;
    temp->next = NULL;


    // 2. Set up traversal pointers

    // prev starts at HEADER
    node_t *prev = list->head;

    // pres starts at first REAL node
    node_t *pres = list->head->next;


    // 3. Find correct insertion position
    while (pres != NULL && pres->data < data)
    {
        prev = pres;
        pres = pres->next;
    }


    // 4. Insert temp between prev and pres
    temp->next = pres;
    prev->next = temp;
}


// Display the list
void display(list_t *list)
{
    // Start at first REAL node,
    // not the header node
    node_t *p = list->head->next;

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}


// Free all DATA nodes
void free_list(list_t *list)
{
    // Start at first real node
    node_t *p = list->head->next;
    node_t *next;

    while (p != NULL)
    {
        // Save next node BEFORE freeing p
        next = p->next;

        free(p);

        p = next;
    }

    // Header remains, but list is now empty
    list->head->next = NULL;
}


int main()
{
    list_t list;

    init_list(&list);

    insert(&list, 20);
    insert(&list, 10);
    insert(&list, 50);
    insert(&list, 30);
    insert(&list, 40);

    display(&list);

    free_list(&list);

    // Since we're completely finished with the list,
    // free the header node too.
    free(list.head);

    return 0;
}

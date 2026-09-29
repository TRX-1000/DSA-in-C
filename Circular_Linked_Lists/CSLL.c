#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;


// Create a new node
node_t *create_node(int data)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));

    temp->data = data;
    temp->next = NULL;

    return temp;
}


// --------------------------------------------------
// INSERT AT BEGINNING
// --------------------------------------------------

void insert_beginning(node_t **last, int data)
{
    node_t *temp = create_node(data);

    // Empty list
    if (*last == NULL)
    {
        temp->next = temp;   // points to itself
        *last = temp;
    }

    // Non-empty list
    else
    {
        temp->next = (*last)->next;  // temp -> old first
        (*last)->next = temp;        // last -> new first
    }
}


// --------------------------------------------------
// INSERT AT END
// --------------------------------------------------

void insert_end(node_t **last, int data)
{
    node_t *temp = create_node(data);

    // Empty list
    if (*last == NULL)
    {
        temp->next = temp;
        *last = temp;
    }

    // Non-empty list
    else
    {
        temp->next = (*last)->next;  // new node -> first
        (*last)->next = temp;        // old last -> new node
        *last = temp;                // new node becomes last
    }
}


// --------------------------------------------------
// INSERT AT POSITION
// Position starts from 1
// --------------------------------------------------

void insert_position(node_t **last, int data, int position)
{
    if (position <= 1)
    {
        insert_beginning(last, data);
        return;
    }

    if (*last == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    node_t *p = (*last)->next;  // first node

    // Move to node at position - 1
    for (int i = 1; i < position - 1; i++)
    {
        p = p->next;

        // We have gone around the entire circle
        if (p == (*last)->next)
        {
            printf("Invalid position\n");
            return;
        }
    }

    // If p is currently the last node,
    // insertion is at the end.
    if (p == *last)
    {
        insert_end(last, data);
        return;
    }

    node_t *temp = create_node(data);

    temp->next = p->next;
    p->next = temp;
}


// --------------------------------------------------
// DELETE FROM BEGINNING
// --------------------------------------------------

void delete_beginning(node_t **last)
{
    // Empty list
    if (*last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // First node
    node_t *temp = (*last)->next;

    // Only one node
    if (temp == *last)
    {
        *last = NULL;
    }

    // Multiple nodes
    else
    {
        (*last)->next = temp->next;
    }

    free(temp);
}


// --------------------------------------------------
// DELETE FROM END
// --------------------------------------------------

void delete_end(node_t **last)
{
    // Empty list
    if (*last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // Only one node
    if ((*last)->next == *last)
    {
        free(*last);
        *last = NULL;
        return;
    }

    // Start from first node
    node_t *p = (*last)->next;

    // Find node immediately before last
    while (p->next != *last)
    {
        p = p->next;
    }

    node_t *temp = *last;

    // New last must point to first node
    p->next = (*last)->next;

    // p becomes new last
    *last = p;

    free(temp);
}


// --------------------------------------------------
// DELETE FROM POSITION
// Position starts from 1
// --------------------------------------------------

void delete_position(node_t **last, int position)
{
    if (*last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (position <= 1)
    {
        delete_beginning(last);
        return;
    }

    node_t *prev = (*last)->next;  // first node

    // Move prev to node before required node
    for (int i = 1; i < position - 1; i++)
    {
        prev = prev->next;

        if (prev == (*last)->next)
        {
            printf("Invalid position\n");
            return;
        }
    }

    node_t *temp = prev->next;

    // Position does not exist
    if (temp == (*last)->next)
    {
        printf("Invalid position\n");
        return;
    }

    // Deleting last node
    if (temp == *last)
    {
        prev->next = (*last)->next;
        *last = prev;
    }

    // Deleting middle node
    else
    {
        prev->next = temp->next;
    }

    free(temp);
}


// --------------------------------------------------
// SEARCH
// --------------------------------------------------

node_t *search(node_t *last, int key)
{
    if (last == NULL)
        return NULL;

    node_t *p = last->next;  // first node

    do
    {
        if (p->data == key)
            return p;

        p = p->next;

    } while (p != last->next);

    return NULL;
}


// --------------------------------------------------
// DISPLAY
// --------------------------------------------------

void display(node_t *last)
{
    if (last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    node_t *p = last->next;  // first node

    do
    {
        printf("%d ", p->data);
        p = p->next;

    } while (p != last->next);

    printf("\n");
}


// --------------------------------------------------
// FREE ENTIRE LIST
// --------------------------------------------------

void free_list(node_t **last)
{
    if (*last == NULL)
        return;

    node_t *first = (*last)->next;
    node_t *p = first;

    do
    {
        node_t *next = p->next;
        free(p);
        p = next;

    } while (p != first);

    *last = NULL;
}


// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main()
{
    node_t *last = NULL;

    insert_end(&last, 10);
    insert_end(&last, 20);
    insert_end(&last, 30);
    insert_end(&last, 40);

    printf("Original: ");
    display(last);

    insert_beginning(&last, 5);

    printf("After inserting 5 at beginning: ");
    display(last);

    insert_end(&last, 50);

    printf("After inserting 50 at end: ");
    display(last);

    insert_position(&last, 25, 4);

    printf("After inserting 25 at position 4: ");
    display(last);

    delete_beginning(&last);

    printf("After deleting beginning: ");
    display(last);

    delete_end(&last);

    printf("After deleting end: ");
    display(last);

    delete_position(&last, 3);

    printf("After deleting position 3: ");
    display(last);

    node_t *result = search(last, 30);

    if (result != NULL)
        printf("30 found\n");
    else
        printf("30 not found\n");

    free_list(&last);

    return 0;
}

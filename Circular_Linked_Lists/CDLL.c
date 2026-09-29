#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} node_t;


// --------------------------------------------------
// CREATE NODE
// --------------------------------------------------

node_t *create_node(int data)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));

    temp->data = data;
    temp->prev = NULL;
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
        temp->next = temp;
        temp->prev = temp;
        *last = temp;
        return;
    }

    node_t *first = (*last)->next;

    temp->next = first;
    temp->prev = *last;

    first->prev = temp;
    (*last)->next = temp;
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
        temp->prev = temp;
        *last = temp;
        return;
    }

    node_t *first = (*last)->next;

    temp->next = first;
    temp->prev = *last;

    (*last)->next = temp;
    first->prev = temp;

    *last = temp;
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

    node_t *first = (*last)->next;
    node_t *p = first;

    // Move p to node BEFORE desired position
    for (int i = 1; i < position - 1; i++)
    {
        p = p->next;

        if (p == first)
        {
            printf("Invalid position\n");
            return;
        }
    }

    // If inserting after current last
    if (p == *last)
    {
        insert_end(last, data);
        return;
    }

    node_t *temp = create_node(data);

    temp->next = p->next;
    temp->prev = p;

    p->next->prev = temp;
    p->next = temp;
}


// --------------------------------------------------
// DELETE FROM BEGINNING
// --------------------------------------------------

void delete_beginning(node_t **last)
{
    if (*last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    node_t *first = (*last)->next;

    // Only one node
    if (first == *last)
    {
        free(first);
        *last = NULL;
        return;
    }

    node_t *new_first = first->next;

    (*last)->next = new_first;
    new_first->prev = *last;

    free(first);
}


// --------------------------------------------------
// DELETE FROM END
// --------------------------------------------------

void delete_end(node_t **last)
{
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

    node_t *temp = *last;
    node_t *first = (*last)->next;
    node_t *new_last = (*last)->prev;

    new_last->next = first;
    first->prev = new_last;

    *last = new_last;

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

    node_t *first = (*last)->next;
    node_t *p = first;

    // Move to required node
    for (int i = 1; i < position; i++)
    {
        p = p->next;

        if (p == first)
        {
            printf("Invalid position\n");
            return;
        }
    }

    // Deleting last node
    if (p == *last)
    {
        delete_end(last);
        return;
    }

    // Delete middle node
    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);
}


// --------------------------------------------------
// SEARCH
// --------------------------------------------------

node_t *search(node_t *last, int key)
{
    if (last == NULL)
        return NULL;

    node_t *first = last->next;
    node_t *p = first;

    do
    {
        if (p->data == key)
            return p;

        p = p->next;

    } while (p != first);

    return NULL;
}


// --------------------------------------------------
// DISPLAY FORWARD
// --------------------------------------------------

void display_forward(node_t *last)
{
    if (last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    node_t *first = last->next;
    node_t *p = first;

    do
    {
        printf("%d ", p->data);
        p = p->next;

    } while (p != first);

    printf("\n");
}


// --------------------------------------------------
// DISPLAY BACKWARD
// --------------------------------------------------

void display_backward(node_t *last)
{
    if (last == NULL)
    {
        printf("List is empty\n");
        return;
    }

    node_t *p = last;

    do
    {
        printf("%d ", p->data);
        p = p->prev;

    } while (p != last);

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

    printf("Forward: ");
    display_forward(last);

    printf("Backward: ");
    display_backward(last);

    insert_beginning(&last, 5);

    printf("After inserting 5 at beginning: ");
    display_forward(last);

    insert_end(&last, 50);

    printf("After inserting 50 at end: ");
    display_forward(last);

    insert_position(&last, 25, 4);

    printf("After inserting 25 at position 4: ");
    display_forward(last);

    delete_beginning(&last);

    printf("After deleting beginning: ");
    display_forward(last);

    delete_end(&last);

    printf("After deleting end: ");
    display_forward(last);

    delete_position(&last, 3);

    printf("After deleting position 3: ");
    display_forward(last);

    node_t *result = search(last, 30);

    if (result != NULL)
        printf("30 found\n");
    else
        printf("30 not found\n");

    free_list(&last);

    return 0;
}

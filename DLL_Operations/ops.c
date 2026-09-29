#include <stdio.h>
#include <stdlib.h>
#include "ops.h"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Node could not be created.\n");
        return NULL;
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    Node* temp;

    if (newNode == NULL) {
        return head;
    }

    if (head == NULL) {
        // If list is empty
        head = newNode;
        return head;
    }

    temp = head;

    // If list is not empty, go to the last node and insert element
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

int sumAll(Node* head) {
    int sum = 0;
    Node* temp = head;

    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

int sumEven(Node* head) {
    int sum = 0;
    Node* temp = head;

    while (temp != NULL) {
        if (temp->data % 2 == 0) {
            sum += temp->data;
        }
        temp = temp->next;
    }
    return sum;
}

int sumOdd(Node* head) {
    int sum = 0;
    Node* temp = head;

    while (temp != NULL) {
        if (temp->data % 2 != 0) {
            sum += temp->data;
        }
        temp = temp->next;
    }
    return sum;
}

void displayForward(Node* head) {
    Node* temp = head;

    if (head == NULL) {
        printf("Empty list: Nothing to print.\n");
        return;
    }

    printf("Forward: ");

    while (temp != NULL) {
        printf("[%d]", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> [NULL]\n");
}

void displayBackward(Node* head) {
    Node* temp = head;

    if (head == NULL) {
        printf("Empty list: Nothing to print.\n");
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next; // Going to the last node of the list
    }

    printf("Backward: ");
    while (temp != NULL) {
        printf("[%d]", temp->data);
        if (temp->prev != NULL) {
            printf(" -> ");
        }
        temp = temp->prev;
    }
    printf(" -> [NULL]\n");
}

int search(Node* head, int key) {
    Node* temp = head;
    int position = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            return position;
        }

        temp = temp->next;
        position++;
    }
    return -1;
}

Node* mergeLists(Node* head1, Node* head2) {
    Node* temp;

    // If the first list is empty
    if (head1 == NULL) {
        return head2;
    }

    // If the second list is empty
    if (head2 == NULL) {
        return head1;
    }

    temp = head1;

    // Go to the last node of the first list, so that we can add the elements of the second list to it
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Now connect the two lists
    temp->next = head2; // Forward link
    head2->prev = temp; // Backward link

    return head1; // Returning head1 because we added the second list to the first one
                  // If we had added the second list to the first one, we would switch head1 and head2 everywhere (and then return head2)
}

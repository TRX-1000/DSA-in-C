#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* tail = NULL;

void insertEnd(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;

    if (tail == NULL) {
        // List is empty: node points to itself
        newNode->next = newNode;
        tail = newNode;
    } else {
        // Insert after tail, before head
        newNode->next = tail->next;  // new node points to head
        tail->next = newNode;        // old tail points to new node
        tail = newNode;              // update tail to new node
    }
}

void insertBeginning(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;

    if (tail == NULL) {
        newNode->next = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;  // new node points to current head
        tail->next = newNode;        // tail now points to new node as head
    }
}

void deleteNode(int value) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* curr = tail->next; // start at head
    struct Node* prev = tail;

    do {
        if (curr->data == value) {
            if (curr == tail && curr->next == tail) {
                // only one node in the list
                tail = NULL;
            } else {
                prev->next = curr->next;
                if (curr == tail) {
                    tail = prev;
                }
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != tail->next); // stop after full loop back to head

    printf("Value %d not found.\n", value);
}

void display() {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* curr = tail->next; // start at head
    do {
        printf("%d -> ", curr->data);
        curr = curr->next;
    } while (curr != tail->next); // stop when back at head
    printf("(back to head)\n");
}

int main() {
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);
    insertBeginning(5);

    printf("List after insertions: ");
    display();

    deleteNode(20);
    printf("List after deleting 20: ");
    display();

    return 0;
}

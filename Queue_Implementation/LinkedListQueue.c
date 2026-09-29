#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* head = NULL;
Node* tail = NULL;

void Enqueue(int x);
void Dequeue();
void Print();
void Free();

int main() {
    int n = 0, ele;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        printf("Enter element #%d: ", i);
        scanf("%d", &ele);
        Enqueue(ele);
        printf("Element added to list using enqueue operation.\n");
    }

    printf("\nOriginal list: ");
    Print();

    for (int i = 1; i <= n; i++) {
        Dequeue();
        printf("List after dequeue #%d: ", i);
        Print();
    }

    // Free();
    // printf("The list was freed using 'free()'.\n");

    return 0;
}

void Enqueue(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = x;
    newNode->next = NULL;

    if (head == NULL && tail == NULL) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void Dequeue() {
    if (head == NULL) {
        printf("Queue empty. Cannot dequeue.\n");
        return;
    }

    Node* temp = head;
    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
    }
    free(temp);
}

void Print() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* void Free() {
    Node* temp = head;
    while (head != NULL) {
        temp = head;
        head = temp->next;
        free(temp);
    }
    tail = NULL;
}

Not really neded because it is already implemented inside the Dequeue function */

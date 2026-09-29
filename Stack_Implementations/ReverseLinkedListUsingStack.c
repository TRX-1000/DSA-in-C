// In a recursive method, we use an implicitly created stack by the computer's memory that is used to execute function calls

// Here, we are using an EXPLICIT stack to reverse the linked list

/*  Steps to use an explicit stack:
 * 1. Use a temporary variable to traverse the list to the end
 * 2. Each time we go to a particular node, we will push the address of that particular node into the stack (what we are actually pushing to the stack is the pointer to that particular node)
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int stack[MAX];
int top = -1;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push(int val);
int pop(void);
Node* createNode(int val);
void insertNode(Node** head, int data);
void Reverse(Node* head);
void printList(Node* head);

int main() {
    struct Node* head = NULL;

    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);

    printf("Original list: ");
    printList(head);

    Reverse(head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}

void push(int val) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = val;
}

int pop() {
    if (top == -1) {
        printf("Stack is empty, nothing to pop.\n");
        return -1;
    }

    return stack[top--];
}

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node** head, int data) {
    Node* new = createNode(data);
    if (*head == NULL) {
        *head = new;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}

void Reverse(Node* head) {
    Node* temp = head;

    // Pushing the node values onto the stack
    while (temp != NULL) {
        push(temp->data);
        temp = temp->next;
    }

    // Popping the node values back into the nodes
    temp = head;
    while (temp != NULL) {
        temp->data = pop();
        temp = temp->next;
    }
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

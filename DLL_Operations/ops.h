#ifndef OPS_H
#define OPS_H

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data);

Node* insertEnd(Node* head, int data);

int sumAll(Node* head);
int sumEven(Node* head);
int sumOdd(Node* head);

void displayForward(Node* head);
void displayBackward(Node* head);

int search(Node* head, int key);

Node* mergeLists(Node* head1, Node* head2);

#endif

// Writing a program to insert a node at the nth position in the list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node;

Node* head; // Global variable

void Insert(int data, int n);
void Print();

int main() {
    head = NULL;
    Insert(2, 1);
    Print();

    Insert(4, 2);
    Print();

    Insert(6, 1);
    Print();

    Insert(3, 3);
    Print();

    Insert(7, 2);
    Print();

    return 0;
}

void Insert(int data, int n) {
    Node *temp1 = (Node *)malloc(sizeof(Node));
    temp1->data = data;
    temp1->link = NULL;

    // Handling special case where insertion is at 1st position:
    if (n == 1) {
        temp1->link = head;
        head = temp1;
        return; // No further execution needed, so return from the function
    }

    Node *temp2 = head;
    for (int i = 0; i < n-2; i++) {
        temp2 = temp2->link;
        // Running the loop for n-2 times will take us to the (n-1)th node in the list
        // So now temp2 points to the (n-1)th node
    }

    temp1->link = temp2->link;
    // Setting the link field of the newly created node to the (n-1)th node. (Step 1)

    temp2->link = temp1;
    // Setting the link of the (n-1)th node to point to the newly created node. (Step 2)
}

/*

For insertion of a node at the nth position we have to perform 2 steps:
1. We have to make the newly created node's link field point to the next node in the list.
2. We have to make the (n-1)th node's link field point to the newly created node.

*/

void Print() {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp -> link != NULL) {
            printf(" -> ");
        }
        temp = temp->link;
    }
    printf(" -> [NULL]");
    printf("\n");
}

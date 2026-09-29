#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head;

Node* GetNewNode(int x);
void InsertAtHead(int x);
void Print();
void ReversePrint();
void FreeList();

int main() {
    head = NULL;

    InsertAtHead(2);
    Print();
    ReversePrint();

    InsertAtHead(4);
    Print();
    ReversePrint();

    InsertAtHead(6);
    Print();
    ReversePrint();

    FreeList();
    return 0;
}

Node* GetNewNode(int x) {
    Node* temp = (Node*)malloc(sizeof(Node));
    // Creates a node in heap memory, so we will have to explicitly clear it.
    // If we do Node* temp, the pointer variable itself is in the stack, but it points to a memory address in the heap
    // We use DMA to prevent destruction of the node after function call finishes.

    temp->data = x;
    temp->prev = NULL;
    temp->next = NULL;

    return temp;
}

void InsertAtHead(int x) {
    Node* newNode = GetNewNode(x);
    // Ass soon as the function call finishes, the variable 'newNode' will be cleared from the memory
    // But the node itself won't be cleared
    // If we instead did: Node newNode, its not a pointer to the newly created node, it is just a node. which will then be cleared from the memory as soon as the function call finishes.

    // INSERTING A NODE WHEN THE LIST IS EMPTY
    if (head == NULL) {
        head = newNode;
        return;
    }

    // INSERTING A NODE WHEN THE LIST IS NOT EMPTY
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}

/*
 * We can write the GetNewNode function in another way:
 * Node* GetNewNode(int x) {
 *  Node temp;
 *  temp.data = x;
 *  temp.prev = NULL;
 *  temp.next = NULL;
 *
 *  return &temp;
 * }
 *
 * But the problem here is that after the new node is created, the stack frame for GetNewNode will be reclaimed after the function finishes. So even though we have the address of the node created, there is no node there. We cannot control allocation and deallocation of memory on stack, it happens automatically. That is why we use the memory on heap.
 *
 * The only way to access something in the heap is by using a pointer
 *
 * When we do it using the proper way, the stack frame of the node is created, then the head is set to new node (when the list is empty, and when it isnt, the other connections are made) and then the stack frame of GetNewNode is cleared from the memory. This ensures proper conenctions are made before the stack frame is cleared.
 */

void Print() {
    Node* temp = head;
    printf("FORWARD: \n");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> [NULL]\n");
}

void ReversePrint() {
    Node* temp = head;
    if (head == NULL) {
        printf("Empty list.\n");
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next; // Traversing the list to reach the last node
    }

    // Printing the elements using the 'prev' pointer
    printf("REVERSE: \n");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf(" -> ");
        }
        temp = temp->prev;
    }
    printf(" -> [NULL]\n");
}

void FreeList() {
    Node* temp = head;
    while (temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    head = NULL;
}

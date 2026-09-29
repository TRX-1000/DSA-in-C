#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* CreateNode(int x);
Node* Build();
void Print(Node* head);
Node* Reverse(Node* head);
void FreeList(Node* head);

int main() {
    Node *head = NULL;
    int pos = 0;

    // Build the list
    head = Build();

    printf("\nOriginal List:\n");
    Print(head);



    printf("\nList after reversing:\n");
    head = Reverse(head);
    Print(head);


    FreeList(head);

    return 0;
}

Node* CreateNode(int x) {
    Node *temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    temp->data = x;
    temp->next = NULL;

    return temp;
}

Node* Build() {
    Node *head = NULL, *tail = NULL;
    int data = 0, n = 0;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data #%d: ", i + 1);
        scanf("%d", &data);

        Node* temp = CreateNode(data);

        if (head == NULL) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    return head;
}

void Print(Node* head) {
    if (!head) {
        printf("Empty list.\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ---> ");
        }
        temp = temp->next;
    }
    printf(" ---> [NULL]\n");
}

Node* Reverse(Node* head) {
    Node* currentNode, *prevNode, *nextNode;
    prevNode = NULL; // Here, previous node will store the address of the previous node, which then eventually becomes the new head after reversing
    currentNode = head;
    while (currentNode != NULL) {
        nextNode = currentNode->next; // Storing the address of the next node before doing anything else so that don't lose access to the other nodes
        currentNode->next = prevNode; // Setting the next field in the currentNode to point to the previous node instead of the next node to reverse it
        prevNode = currentNode; // Changing the address which the previous node points to so that the next time round the last node will be pointed to
                                // by the second last node
        currentNode = nextNode; // Shifting the current node to the next node in the list so that this process can happen for all the nodes in the list
    }
    head = prevNode; // At the start of the function, prevNode was set to NULL, as the first node in the original list would have to point to NULL to signify the end of the list once it was reversed. Now, the new start of the list is actually the last node, so we are adjusting where the head points to

    return head;
}

void FreeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

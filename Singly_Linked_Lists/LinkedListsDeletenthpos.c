#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* CreateNode(int x);
Node* Build();
void Print(Node* head);
Node* Delete(Node* head, int pos);
void FreeList(Node* head);

int main() {
    Node *head = NULL;
    int pos = 0;

    // Build the list
    head = Build();

    printf("\nOriginal List:\n");
    Print(head);

    // Prompt for deletion
    printf("\nEnter the position to delete (1-indexed): ");
    if (scanf("%d", &pos) == 1) {
        head = Delete(head, pos);

        printf("\nList after deletion:\n");
        Print(head);
    }

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

Node* Delete(Node* head, int pos) {
    if (head == NULL) {
        printf("List is empty. Cannot delete any element.\n");
        return NULL;
    }

    Node* temp = head;

    // Case 1: Deleting the head node (1st position)
    if (pos == 1) {
        head = head->next;
        free(temp);
        return head;
    }

    // Case 2: Deleting any other node
    // Traverse to the (pos - 1)th node
    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    // Check if position entered is out of bounds
    if (temp == NULL || temp->next == NULL) {
        printf("Position entered is out of bounds.\n");
        return head;
    }

    // Node to be deleted is temp->next
    Node* targetNode = temp->next;
    Node* nextNode = targetNode->next; // Node after the target node

    temp->next = nextNode; // Link the nodes before and after the target node
    free(targetNode);

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

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
Node* CreateNode(int x);
Node* Build();
void Print(Node* head);
Node* ReverseRecursive(Node* head);
void FreeList(Node* head);

int main() {
    Node* head = NULL;

    head = Build();

    printf("\nOriginal List:\n");
    Print(head);

    head = ReverseRecursive(head);

    printf("\nList after recursive reversal:\n");
    Print(head);

    FreeList(head);

    return 0;
}

Node* CreateNode(int x) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
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
        printf("Enter data for field #%d: ", i + 1);
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

Node* ReverseRecursive(Node* head) {
    // Base Case: If the list is empty or has only one node, it's already reversed
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* newHead = ReverseRecursive(head->next);

    head->next->next = head;

    head->next = NULL;

    return newHead;
}

void FreeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

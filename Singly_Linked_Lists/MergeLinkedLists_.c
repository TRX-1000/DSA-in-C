#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head;

void Insert(int x);
void CreateNode(int data);
void Print();

int main() {
    int n = 0, data = 0;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter data for node #%d: ", i + 1);
        scanf("%d", &data);
        CreateNode(data);
    }
    Print();
}

void CreateNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    temp->next = head;
    head = temp;
}

void Print() {
    int count = 1;
    Node* temp = head;
    while (temp != NULL) {
        printf("Link %d: %d\n", count, temp->data);
        temp = temp->next;
        count++;
    }
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
void InorderTraversal(Node* rootPtr);
int Search(Node* rootPtr, int data);

int main(void) {
    Node* rootPtr = NULL;
    int data;
    int n;

    printf("Enter the number of elements in the tree: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Element #%d: ", i + 1);
        scanf("%d", &data);
        rootPtr = Insert(rootPtr, data);
    }

    printf("\n");

    return 0;
}

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


Node* Insert(Node* rootPtr, int data) {
    if (rootPtr == NULL) {
        rootPtr = GetNewNode(data);
    } else if (data <= rootPtr->data) {
        rootPtr->left = Insert(rootPtr->left, data); // Recursive funtion

    } else {
        rootPtr->right = Insert(rootPtr->right, data); // Else, right sub-tree
    }
    return rootPtr;
}

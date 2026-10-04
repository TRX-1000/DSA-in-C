// Height of tree = number of edges in longest path from root to a leaf node
// Height of a node = number of edges in longest path from that node to a leaf node
// Height of tree with 1 node = 0
// Depth of a tree = number of edges in th path from root to that node

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
int FindHeight(Node* rootPtr);
int max(int a, int b); // Helper function

int main() {
    Node* rootPtr = NULL;
    int n = 0, data = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);
        rootPtr = Insert(rootPtr, data);
    }

    printf("\nHeight of the tree = %d\n", FindHeight(rootPtr));

    return 0;
}

Node* GetNewNode(int data) {
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode->data = data;
    NewNode->left = NewNode->right = NULL;
    return NewNode;
}

Node* Insert(Node* rootPtr, int data) {
    if (rootPtr == NULL) {
        GetNewNode(data);
    } else if (data <= rootPtr->data) {
        rootPtr->left = Insert(rootPtr->left, data);
    } else {
        rootPtr->right = Insert(rootPtr->right, data);
    }

    return rootPtr;

}

int FindHeight(Node* rootPtr) {
    if (rootPtr == NULL) {
        return -1;
    }
    int leftHeight = FindHeight(rootPtr->left);
    int rightHeight = FindHeight(rootPtr->right);

    return (max(leftHeight, rightHeight) + 1);
}

int max (int a, int b) {
    return (a > b ? a : b);
}

// In the FindHeight function, we are returning the max of the right subtree and the left subtree + 1.
// The base case is returning -1 because the height of an empty tree is -1 by convention
// AND for a leaf node the height is 0, so the edge from the leaf node to NULL (doesn't exist, but still getting counted) will be balanced by the +1 in the recursive function call

// Time complexity of the FindHeight function is O(n)

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
int FindHeight(Node* rootPtr);
int max(int a, int b); // Helper function

int main(void) {
    Node* rootPtr = NULL; // empty tree to start
    int n = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int data = 0;
        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);
        rootPtr = Insert(rootPtr, data);
    }

    InorderTraversal(rootPtr); // should print 10 15 20 (sorted order)
    printf("\n");

    int key;
    printf("Enter the element to be searched: ");
    scanf("%d", &key);
    if (Search(rootPtr, key)) {
        printf("Element was found.\n");
    } else {
        printf("Element was not found.\n");
    }

    printf("Height of the binary search tree is: %d\n", FindHeight(rootPtr));

    return 0;
}

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Inserts `data` into the tree rooted at rootPtr and returns the
// (possibly new) root of that subtree. The caller must reassign:
//     rootPtr = Insert(rootPtr, data);
// because when rootPtr is NULL, this function allocates a new node
// and hands its address back up through the return value.

Node* Insert(Node* rootPtr, int data) {
    if (rootPtr == NULL) {
        rootPtr = GetNewNode(data);
    } else if (data <= rootPtr->data) {
        rootPtr->left = Insert(rootPtr->left, data); // Recursive funtion
        // If the data to be entered is lesser than the root, we have to insert it in the left sub-tree
    } else {
        rootPtr->right = Insert(rootPtr->right, data); // Else, right sub-tree
    }
    return rootPtr;
}

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) return;
    InorderTraversal(rootPtr->left);
    printf("%d ", rootPtr->data);
    InorderTraversal(rootPtr->right);
}

int Search(Node* rootPtr, int data) {
    if (rootPtr == NULL) {
        return 0;
    }

    if (rootPtr->data == data) {
        return 1;
    } else if (data <= rootPtr->data) {
        // Search in left sub-tree
        return Search(rootPtr->left, data);
    } else {
        // Search right sub-tree
        return Search(rootPtr->right, data);
    }
}

int FindHeight(Node* rootPtr) {

    if (rootPtr == NULL) {
        return -1; // If we return 0, that will mean the height of a leaf node will be 1, which is not true. The
                   // The height of a leaf node is always 0. So we return -1, so that it gets nullified to 0 in the return statement.
                   // And also, by convention, height of an empty tree is set to be -1
    }

    int leftHeight = FindHeight(rootPtr->left);
    int rightHeight = FindHeight(rootPtr->right);

    return (max(leftHeight, rightHeight) + 1);
}

int max(int a, int b) {
    return (a > b ? a : b);
}

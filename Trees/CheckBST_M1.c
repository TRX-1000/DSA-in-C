/*
 * A binary tree is a tree in which a node can have at most 2 children.

 * A binary search tree is a tree in which for each node, value of all the nodes in left subtree is lesser than or equal to the root node, and value of all the nodes in right subtree is greater than the root node.
 * It is a recursive structure in which all the left subtrees are binary search trees with the left node lesser than the root and the right node greater than the root.

 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
int IsSubtreeLesser(Node* rootPtr, int value);
int IsSubtreeGreater(Node* rootPtr, int value);
int IsBinarySearchTree(Node* rootPtr);

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

    printf("%s\n", (IsBinarySearchTree(rootPtr) ? "Binary search tree" : "Not binary search tree"));

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
        rootPtr->left = Insert(rootPtr->left, data);

    } else {
        rootPtr->right = Insert(rootPtr->right, data);
    }
    return rootPtr;
}

int IsBinarySearchTree(Node* rootPtr) {
    if (rootPtr == NULL) {
        return 1;
    }
    if (IsSubtreeLesser(rootPtr->left, rootPtr->data) &&
        IsSubtreeGreater(rootPtr->right, rootPtr->data) &&
        IsBinarySearchTree(rootPtr->left) &&
        IsBinarySearchTree(rootPtr->right)) {
            return 1;
        } else {
            return 0;
        }
}

int IsSubtreeLesser(Node* rootPtr, int value) {
    if (rootPtr == NULL) {
        return 1;
    }
    if (rootPtr->data <= value &&
        IsSubtreeLesser(rootPtr->left, value) &&
        IsSubtreeLesser(rootPtr->right, value)) {
            return 1;
        } else {
            return 0;
        }
}

int IsSubtreeGreater(Node* rootPtr, int value) {
    if (rootPtr == NULL) {
        return 1;
    }
    if (rootPtr->data <= value &&
        IsSubtreeGreater(rootPtr->left, value) &&
        IsSubtreeGreater(rootPtr->right, value)) {
            return 1;
        } else {
            return 0;
        }
}

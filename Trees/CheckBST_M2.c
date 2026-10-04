/*
 * The first method is correct, but it involves a lot of traversal, which is very expensive.
 * In the second method, we define a range for each node based on the position.
 * For example, if the root has the value x, the permissible range for the left child would be -inf to x, and the permissible range for the right child would be x to inf.
 * This goes on recursively for each child node.
 */

#include <stdio.h>
#include <stdlib.h>

#define INT_MIN -99999
#define INT_MAX 99999

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
int IsBSTUtil(Node* rootPtr, int min_val, int max_val);
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

int IsBSTUtil(Node* rootPtr, int min_val, int max_val) {
    if (rootPtr == NULL) {
        return 1;
    }
    if (rootPtr->data > min_val &&
        rootPtr->data < max_val &&
        IsBSTUtil(rootPtr->left, min_val, rootPtr->data) &&
        IsBSTUtil(rootPtr->right, rootPtr->data, max_val)) {
            return 1;
        } else {
            return 0;
        }
}

int IsBinarySearchTree(Node* rootPtr) {
    return IsBSTUtil(rootPtr, INT_MIN, INT_MAX);
}


/*
 * IsBinarySearchTree(rootPtr->left, min_val, root->data) => The parameters here mean that for the left child, the lower bound is the minimum value and the upper bound is the root

 * IsBinarySearchTree(rootPtr->left, root->data, max_val) => Here it means that for the right child, the lower bound is the root and the upper bound is the maximum value

 * INT_MIN and INT_MAX => Macros for minimum and maximum possible values respectively for int
 */

// Another possible solution -> traverse the tree in inorder methos, we will get a list. If list is sorted = BST, otherwise not BST

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);

Node* RightRotate(Node* y);
Node* LeftRotate(Node* x);

Node* Delete(Node* rootPtr, int data);
Node* Splay(Node* rootPtr, int data);

int main() {
    Node* rootPtr = NULL;
    int n = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int data;

        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);

        rootPtr = Insert(rootPtr, data);
    }

    printf("\nSplay Tree created successfully.\n");

    return 0;
}

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* RightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

Node* LeftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

Node* Insert(Node* rootPtr, int data) {

    if (rootPtr == NULL) {
        return GetNewNode(data);
    }

    rootPtr = Splay(rootPtr, data);

    if (rootPtr->data == data) {
        printf("Duplicate values not allowed.\n");
        return rootPtr;
    }

    Node* newNode = GetNewNode(data);

    if (data < rootPtr->data) {

        newNode->right = rootPtr;
        newNode->left = rootPtr->left;

        rootPtr->left = NULL;
    } else {

        newNode->left = rootPtr;
        newNode->right = rootPtr->right;

        rootPtr->right = NULL;
    }

    return newNode;
}

Node* Splay(Node* rootPtr, int data) {

    // Empty tree or element already at root
    if (rootPtr == NULL || rootPtr->data == data) {
        return rootPtr;
    }

    // Element lies in left subtree
    if (data < rootPtr->data) {

        if (rootPtr->left == NULL) {
            return rootPtr;
        }

        // Zig-Zig (Left-Left)
        if (data < rootPtr->left->data) {
            rootPtr->left->left =
                Splay(rootPtr->left->left, data);

            rootPtr = RightRotate(rootPtr);
        }

        // Zig-Zag (Left-Right)
        else if (data > rootPtr->left->data) {
            rootPtr->left->right =
                Splay(rootPtr->left->right, data);

            if (rootPtr->left->right != NULL) {
                rootPtr->left =
                    LeftRotate(rootPtr->left);
            }
        }

        // Final rotation
        if (rootPtr->left == NULL) {
            return rootPtr;
        }

        return RightRotate(rootPtr);
    }

    // Element lies in right subtree
    else {

        if (rootPtr->right == NULL) {
            return rootPtr;
        }

        // Zig-Zig (Right-Right)
        if (data > rootPtr->right->data) {
            rootPtr->right->right =
                Splay(rootPtr->right->right, data);

            rootPtr = LeftRotate(rootPtr);
        }

        // Zig-Zag (Right-Left)
        else if (data < rootPtr->right->data) {
            rootPtr->right->left =
                Splay(rootPtr->right->left, data);

            if (rootPtr->right->left != NULL) {
                rootPtr->right =
                    RightRotate(rootPtr->right);
            }
        }

        // Final rotation
        if (rootPtr->right == NULL) {
            return rootPtr;
        }

        return LeftRotate(rootPtr);
    }
}       

Node* Delete(Node* rootPtr, int data) {

    if (rootPtr == NULL) {
        return NULL;
    }

    rootPtr = Splay(rootPtr, data);

    if (rootPtr->data != data) {
        printf("Element not found.\n");
        return rootPtr;
    }

    Node* newRoot;

    if (rootPtr->left == NULL) {
        newRoot = rootPtr->right;
    } else {
        Node* rightSubtree = rootPtr->right;

        newRoot = Splay(rootPtr->left, data);

        newRoot->right = rightSubtree;
    }

    free(rootPtr);

    return newRoot;
}
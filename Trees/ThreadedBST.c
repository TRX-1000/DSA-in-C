#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;

    struct Node* right;
    struct Node* left;

    int lThread;
    int rThread;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
void InorderTraversal(Node* rootPtr);

int main() {
    Node* rootPtr = NULL;
    int n = 0;
    int data = 0;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);
        rootPtr = Insert(rootPtr, data);
    }

    printf("\nInorder traversal: \n");
    InorderTraversal(rootPtr);
    printf("\n");

}

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Node could not be allocated.\n");
        return NULL;
    }

    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    newNode->lThread = 1;
    newNode->rThread = 1;
    // When node is created, it doesn't have any children
    // So when we set both right and left threads as 1, we are saying:
    // "Left and right are available to behave as threads rather than child links"

    return newNode;
}

Node* Insert(Node* rootPtr, int data) {
    Node* current = rootPtr;
    Node* parent = NULL;

    // First, find the position where the new node must be inserted
    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            // Go left only if there is an actual left child
            if (current->lThread == 0) {
                current = current->left;
            } else {
                break;
            }
        } else if (data > current->data) {
            // Go right only if there is an actual right child
            if (current->rThread == 0) {
                current = current->right;
            } else {
                break;
            }
        } else {
            printf("Duplicate values not allowed.\n");
            return rootPtr;
        }
    }

    Node* newNode = GetNewNode(data);

    if (parent == NULL) {
        // Empty tree condtion
        rootPtr = newNode;
    } else if (data < parent->data) {
        // Insert as left child
        newNode->left = parent->left;
        newNode->right = parent;

        parent->lThread = 0;
        parent->left = newNode;
    } else {
        // Insert as right child
        newNode->left = parent;
        newNode->right = parent->right;

        parent->rThread = 0;
        parent->right = newNode;
    }

    return rootPtr;
}

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return;
    }

    Node* current = rootPtr;

    /* Go to the leftmost node */
    while (current->lThread == 0) {
        current = current->left;
    }

    while (current != NULL) {

        printf("[%d] ", current->data);

        // If right pointer is a thread, follow it to inorder successor
        if (current->rThread == 1) {
            current = current->right;
        } else {
            // Otherwise go to right subtree, then find its leftmost node

            current = current->right;

            while (current != NULL && current->lThread == 0) {
                current = current->left;
            }
        }
    }
}

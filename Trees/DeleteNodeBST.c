#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
Node* Delete(Node* rootPtr, int key);
Node* FindMin(Node* rootPtr); // Helper function to find the address of the smallest node in the right subtree
void InorderTraversal(Node* rootPtr);


int main() {
    Node* rootPtr = NULL;
    int n = 0;
    int data = 0;
    int key = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);

        rootPtr = Insert(rootPtr, data);
    }

    printf("\nTree before deletion: ");
    InorderTraversal(rootPtr);

    printf("\n\nEnter the element to delete: ");
    scanf("%d", &key);

    rootPtr = Delete(rootPtr, key);

    printf("\nTree after deletion: ");
    InorderTraversal(rootPtr);

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
        rootPtr->left = Insert(rootPtr->left, data);
    } else {
        rootPtr->right = Insert(rootPtr->right, data);
    }
    return rootPtr;
}

Node* Delete(Node* rootPtr, int key) {
    if (rootPtr == NULL) {
        printf("Key not found.\n");
        return NULL;
    } else if (key < rootPtr->data) {
        rootPtr->left = Delete(rootPtr->left, key); // Go into the left subtree
    } else if (key > rootPtr->data) {
        rootPtr->right = Delete(rootPtr->right, key); // Go into the right subtree
    } else {
        // Found the node for deletion

        if (rootPtr->left == NULL && rootPtr->right == NULL) {
            /* CASE 1: NO CHILDREN NODES */
            free(rootPtr);
            rootPtr = NULL;
        } else if (rootPtr->left == NULL) {
            /* CASE 2A: TARGET NODE HAS RIGHT CHILD */
            Node* temp = rootPtr;
            rootPtr = rootPtr->right;
            free(temp);
        } else if (rootPtr->right == NULL) {
            /* CASE 2B: TARGET NODE HAS LEFT CHILD */
            Node* temp = rootPtr;
            rootPtr = rootPtr->left;
            free(temp);
        } else {
            /*
             * First, we have to find the minimum value in the right subtree of the element that we are trying to delete.
             * We need a function that returns the address of the node with the minimum value.
             * Then we have to set the data in the node we are trying to delete as the the minimum value.
             * Now this problem is reduced to Case 1 OR Case 2A
             */

            Node* temp = FindMin(rootPtr->right);
            rootPtr->data = temp->data;
            rootPtr->right = Delete(rootPtr->right, temp->data);
        }
    }
    return rootPtr;
}

Node* FindMin(Node* rootPtr) {
    if (rootPtr == NULL) {
        return NULL;
    }
    Node* current = rootPtr;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

/*
 * Case 1 can be handled by the same logic as Case 2.
 *
 * If the node is a leaf, both left and right are NULL.
 * Therefore rootPtr->left == NULL is true.
 *
 * We set:
 *     rootPtr = rootPtr->right;
 *
 * Since right is also NULL, rootPtr becomes NULL.
 * We then free the original node.
 *
 * Therefore a separate leaf case is unnecessary.
 */

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) return;
    InorderTraversal(rootPtr->left);
    printf("%d ", rootPtr->data);
    InorderTraversal(rootPtr->right);
}

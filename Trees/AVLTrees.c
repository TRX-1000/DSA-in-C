#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;


/* Function prototypes */

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);

Node* RightRotate(Node* y);
Node* LeftRotate(Node* x);

int Height(Node* rootPtr);
int Max(int a, int b);
int GetBalance(Node* rootPtr);

void InorderTraversal(Node* rootPtr);


int main(void) {
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

    printf("\nInorder traversal of AVL Tree: ");
    InorderTraversal(rootPtr);

    printf("\n");

    return 0;
}


/* Create a new node */

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = data;

    newNode->left = NULL;
    newNode->right = NULL;

    /* Leaf node has height 0 */
    newNode->height = 0;

    return newNode;
}


/* Return height of node */

int Height(Node* rootPtr) {
    if (rootPtr == NULL) {
        return -1;
    }

    return rootPtr->height;
}


/* Return larger value */

int Max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}


/* Calculate balance factor */

int GetBalance(Node* rootPtr) {
    if (rootPtr == NULL) {
        return 0;
    }

    return Height(rootPtr->left)
         - Height(rootPtr->right);
}


/* Right Rotation */

Node* RightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    /* Perform rotation */

    x->right = y;
    y->left = T2;


    /* Update heights */

    y->height =
        1 + Max(Height(y->left),
                Height(y->right));

    x->height =
        1 + Max(Height(x->left),
                Height(x->right));


    /* x becomes new root */

    return x;
}


/* Left Rotation */

Node* LeftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    /* Perform rotation */

    y->left = x;
    x->right = T2;


    /* Update heights */

    x->height =
        1 + Max(Height(x->left),
                Height(x->right));

    y->height =
        1 + Max(Height(y->left),
                Height(y->right));


    /* y becomes new root */

    return y;
}


/* Insert node into AVL Tree */

Node* Insert(Node* rootPtr, int data) {

    /* Normal BST insertion */

    if (rootPtr == NULL) {
        return GetNewNode(data);
    }

    if (data < rootPtr->data) {
        rootPtr->left =
            Insert(rootPtr->left, data);
    }

    else if (data > rootPtr->data) {
        rootPtr->right =
            Insert(rootPtr->right, data);
    }

    else {
        printf("Duplicate values not allowed.\n");
        return rootPtr;
    }


    /* Update height of current node */

    rootPtr->height =
        1 + Max(Height(rootPtr->left),
                Height(rootPtr->right));


    /* Calculate balance factor */

    int balance = GetBalance(rootPtr);


    /* -------- LL Case -------- */

    if (balance > 1 &&
        data < rootPtr->left->data) {

        return RightRotate(rootPtr);
    }


    /* -------- RR Case -------- */

    if (balance < -1 &&
        data > rootPtr->right->data) {

        return LeftRotate(rootPtr);
    }


    /* -------- LR Case -------- */

    if (balance > 1 &&
        data > rootPtr->left->data) {

        rootPtr->left =
            LeftRotate(rootPtr->left);

        return RightRotate(rootPtr);
    }


    /* -------- RL Case -------- */

    if (balance < -1 &&
        data < rootPtr->right->data) {

        rootPtr->right =
            RightRotate(rootPtr->right);

        return LeftRotate(rootPtr);
    }


    /* No imbalance */

    return rootPtr;
}


/* Inorder Traversal */

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return;
    }

    InorderTraversal(rootPtr->left);

    printf("%d ", rootPtr->data);

    InorderTraversal(rootPtr->right);
}

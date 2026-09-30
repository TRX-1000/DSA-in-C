#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);

void LevelorderTraversal(Node* rootPtr);
void InorderTraversal(Node* rootPtr);
void PreorderTraversal(Node* rootPtr);
void PostorderTraversal(Node* rootPtr);

void InitQueue(Queue *q);
void Enqueue(Queue *q, Node* treeNode);
Node* Dequeue(Queue *q);
int IsQueueEmpty(Queue *q);

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

    printf("\n");

    printf("\nPreorder: ");
    PreorderTraversal(rootPtr);

    printf("\nInorder: ");
    InorderTraversal(rootPtr);

    printf("\nPostorder: ");
    PostorderTraversal(rootPtr);

    printf("\nLevel order: ");
    LevelorderTraversal(rootPtr);

    printf("\n");
}

Node* GetNewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->right = newNode->left = NULL;
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

void PreorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return;
    }

    printf("[%d] ", rootPtr->data);
    PreorderTraversal(rootPtr->left);
    PreorderTraversal(rootPtr->right);
}

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return;
    }

    InorderTraversal(rootPtr->left);
    printf("[%d] ", rootPtr->data);
    InorderTraversal(rootPtr->right);
}

void PostorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return;
    }

    PostorderTraversal(rootPtr->left);
    PostorderTraversal(rootPtr->right);
    printf("[%d] ", rootPtr->data);
}

/* EXPLANATION FOR LEVEL-ORDER TRAVERSAL */
/*

As we visit a node, we keep references to its children
in a queue so that we can visit them later.

Discovered node: Node is in the queue, but has not been visited yet.

Algorithm:

1. Enqueue root.

2. While queue is not empty:
      a. Dequeue front node.
      b. Visit it.
      c. Enqueue its left child, if present.
      d. Enqueue its right child, if present.

Since a queue follows FIFO:

    First discovered -> First visited

Therefore nodes are visited level by level.

*/

void LevelorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) {
        return; 
    }

    Queue q; // actual queue variable, so we pass address of q (&q) to IsQueueEmpty as it expects a pointer to a queue
    InitQueue(&q);
    Enqueue(&q, rootPtr);

    while (!IsQueueEmpty(&q)) {
        Node* current = Dequeue(&q);
        printf("[%d] ", current->data);

        // now enqueue the children
        if (current->left != NULL) {
            Enqueue(&q, current->left);
        } 
        if (current->right != NULL) {
            Enqueue(&q, current->right);
        }
    }
}

void InitQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

void Enqueue(Queue *q, Node* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));     
    newNode->treeNode = treeNode;
    newNode->next = NULL;

    // If queue is empty:
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
        return;
    }

    // Else, add new node afer current rear:
    q->rear->next = newNode;
    q->rear = newNode; // Move rear to the newly added node
}

Node* Dequeue(Queue *q) {
    if(IsQueueEmpty(q)) {
        return NULL;
    }

    // Here, we are passing only q to the IsQueueEmpty function because the parameter is already Queue* q, which is a pointer to q

    QueueNode* temp = q->front; // temp points to the front of the queue
    Node* treeNode = temp->treeNode; // Save the tree node before deleting the queue node
    q->front = q->front->next; // Move forward

    // if queue became empty, the rear also must become NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);

    return treeNode;

}

int IsQueueEmpty(Queue* q) {
    return q->front == NULL; // returns 1 if true, 0 if false
}
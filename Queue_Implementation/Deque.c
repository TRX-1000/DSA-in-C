#include <stdio.h>

#define MAX 5

typedef struct {
    int arr[MAX];
    int front;
    int rear;
} Deque;


// Initialize deque
void initDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}


// Check if deque is empty
int isEmpty(Deque *dq) {
    return (dq->front == -1);
}


// Check if deque is full
int isFull(Deque *dq) {
    return ((dq->front == 0 && dq->rear == MAX - 1) ||
            (dq->front == dq->rear + 1));
}


// Insert at FRONT
void insertFront(Deque *dq, int x) {

    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }

    // First element
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    }

    // front is at beginning -> wrap around
    else if (dq->front == 0) {
        dq->front = MAX - 1;
    }

    // Move front backwards
    else {
        dq->front--;
    }

    dq->arr[dq->front] = x;
}


// Insert at REAR
void insertRear(Deque *dq, int x) {

    if (isFull(dq)) {
        printf("Deque Overflow\n");
        return;
    }

    // First element
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    }

    // rear is at end -> wrap around
    else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    }

    // Move rear forward
    else {
        dq->rear++;
    }

    dq->arr[dq->rear] = x;
}


// Delete from FRONT
int deleteFront(Deque *dq) {

    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return -1;
    }

    int x = dq->arr[dq->front];

    // Only one element
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    }

    // front is at last index -> wrap around
    else if (dq->front == MAX - 1) {
        dq->front = 0;
    }

    // Move front forward
    else {
        dq->front++;
    }

    return x;
}


// Delete from REAR
int deleteRear(Deque *dq) {

    if (isEmpty(dq)) {
        printf("Deque Underflow\n");
        return -1;
    }

    int x = dq->arr[dq->rear];

    // Only one element
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    }

    // rear is at first index -> wrap around
    else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    }

    // Move rear backwards
    else {
        dq->rear--;
    }

    return x;
}


// Display deque
void display(Deque *dq) {

    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }

    int i = dq->front;

    printf("Deque: ");

    while (1) {

        printf("%d ", dq->arr[i]);

        if (i == dq->rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
}


int main() {

    Deque dq;

    initDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertRear(&dq, 30);

    insertFront(&dq, 5);

    display(&dq);

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear: %d\n", deleteRear(&dq));

    display(&dq);

    return 0;
}

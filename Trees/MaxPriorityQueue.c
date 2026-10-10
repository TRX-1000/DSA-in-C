#include <stdio.h>

#define MAX 100

int heap[MAX];
int size = 0;

void Insert(int data);
int DeleteMax();
int Peek();

int main(void) {
    Insert(50);
    Insert(30);
    Insert(80);
    Insert(60);

    printf("Highest priority element: %d\n", Peek());

    printf("Deleted: %d\n", DeleteMax());

    printf("Highest priority element now: %d\n", Peek());

    return 0;
}

void Insert(int data) {
    if (size == MAX) {
        printf("Priority queue is full.\n");
        return;
    }

    int i = size;

    heap[i] = data;
    size++;

    while (i != 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i]) {
            break;
        }

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

int Peek() {
    if (size == 0) {
        printf("Priority queue is empty.\n");
        return -1;
    }

    return heap[0];
}

int DeleteMax() {
    if (size == 0) {
        printf("Priority queue is empty.\n");
        return -1;
    }

    int deletedElement = heap[0];

    heap[0] = heap[size - 1];
    size--;

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == i) {
            break;
        }

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }

    return deletedElement;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int size = 0;

void Insert(int data);
void DeleteMax();

int main() {
    // Stuff
    return 0;
}

void Insert(int data) {
    if (size == MAX) {
        printf("The heap is full.\n");
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

int DeleteMax() {
    if (size == 0) {
        printf("Heap is empty.\n");
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

/*
 * For min-heap arrays, the only difference is that the conditions for swapping are reversed.
 * The child must be greater than the parent
 * So for insertion: heap[parent] >= child will result in swapping
 * And for deletion: Same code as max-heap, just choose the smaller child instead of the larger child.
 * heap[left] < heap[smallest] -> smallest = left
 * heap[right] < heap[smallest] -> smallest = right
 */

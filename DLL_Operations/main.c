#include <stdio.h>
#include "ops.h"

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;

    int n = 0, key = 0, data = 0, position = 0;

    printf("Enter the number of elements in List 1: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Element #%d: ", i + 1);
        scanf("%d", &data);

        head1 = insertEnd(head1, data);
    }

    printf("\n");

    // Display list 1
    displayForward(head1);
    displayBackward(head1);

    printf("\n");

    // Displaying sum of elements
    printf("Sum of all the elements: %d\n", sumAll(head1));
    printf("Sum of even elements: %d\n", sumEven(head1));
    printf("Sum of odd elements: %d\n", sumOdd(head1));

    printf("\n");

    // Searching for an element
    printf("Enter the element to be searched: ");
    scanf("%d", &key);

    position = search(head1, key);

    if (position == -1) {
        printf("Element was not found in List 1.\n");
        printf("\n\n");
    } else {
        printf("Element found at position %d.\n", position);
        printf("\n\n");
    }

    // Creating list 2
    printf("Enter the number of elements in List 2: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Element #%d: ", i + 1);
        scanf("%d", &data);

        head2 = insertEnd(head2, data);
    }

    // Merging both lists
    head1 = mergeLists(head1, head2);

    printf("\n");

    // Print lists after merging
    printf("After merging: ");
    displayForward(head1);
    displayBackward(head1);
}

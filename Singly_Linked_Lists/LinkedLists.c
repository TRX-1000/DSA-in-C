#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *link;
} Node;

Node *head;

void Insert(int x); // Function to insert a node at the beginning of the list
void Print();

int main() {
    head = NULL;

    int n = 0, x = 0;
    printf("Enter number of data entries: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Node *temp = (Node*)malloc(sizeof(Node));
        printf("Enter data: ");
        scanf("%d", &x);

        Insert(x); // Function to insert a node at the start of the list
        Print(); // Function to print the data in all the nodes in the linked list everytime a node is added
    }

    return 0;
}

void Insert(int x) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x; // Setting the data field in the node to store the data
    temp->link = NULL; // Setting the link field of the node to point to NULL, can be modified everytime

    temp->link = head; // This sets the link field of the newly created node to point to the head node
    head = temp; // This makes the newly created node the head node

    // This also covers the scenario when the list is empty
}

void Print() {
    Node *temp = head;
    printf("List: \n");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->link != NULL) {
            printf(" -> ");
        }
        temp = temp->link;
    }
    printf("-> [NULL]");
    printf("\n");
}


/*
THERE IS ONE MORE WAY TO WRITE THE SAME PROGRAM:

Instead of declaring the global variable head, we pass the head pointer as an argument to the functions and define the head variable in the main function. This passes two separate copies to each function, so we can use the head pointer to directly traverse the function instead of the temp pointer

void Print(Node *head1);
Then we can remove the statement Node *temp = head and use the head pointer in the while loop

void Insert(Node *head2, int x);
After the list is modified, the head in the main method should also be modified

There are two ways to do this:

METHOD 1: Set the return type of the Insert function to be Node* instead of void. This way, we can return the modified address that the head pointer is pointing to using the statement 'return temp;'. Then in the main function, we will have to collect the new head pointer using head = Insert(head, x)

Node* Insert(Node* head, int x) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->link = NULL;

    temp->link = head;
    head = temp;

    return temp;

}

int main() {
    head = NULL;

    int n = 0, x = 0;
    printf("Enter number of data entries: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Node *temp = (Node*)malloc(sizeof(Node));
        printf("Enter data: ");
        scanf("%d", &x);

        head = Insert(head, x);
        Print(head);
    }

    return 0;
}



METHOD 2: Pass a pointer to the head pointer to the Insert function, so that the function can directly modify head in main without needing to return anything or reassign head = Insert(...). Since head is already a pointer to a Node, a pointer to head itself is a Node **. Inside Insert, we dereference once (*pointerToHead) to access or modify the actual head variable in main.

with no head = ... needed, because Insert is void — it doesn't hand anything back, it just reaches into main's head variable through the pointer and changes it directly.

void Insert(Node **pointerToHead, int x) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->link = NULL;

    if (*pointerToHead != NULL) {
    temp->link = *pointerToHead;
    }

    *pointerToHead = temp;

}

and in the main function:
Insert(&head, x);

*/

// Inorder successor for a given node is the element that will be printed next during the traversal of BST

// Figuring out the successor while traversing the tree is expensive. Most frequently performed operations (insertion, deletion, searching, etc.) happen in O(h) (h = height of the tree). It would be good to find the successor and predecessor in O(h).

/* Logic: 
CASE 1: Node has right subtree - 
For the node that we want to find the inorder successor of, we go to the right subtree, and then travel as far left as possible. So the inorder successor is the left-most node in the right subtree. (For BST, minimum value in its right subtree). 

CASE 2: Node doesn't have a right subtree -
We have to go back to the parent. 

If we are going to the parent from the left, then the parent (which was un-visited) would be the inorder successor to the target node. 

If we are going to the parent from the right, the parent would have already been visited. So the recursion rolls back and we visit the parent of the parent. We visit that node, which would then be the successor.

Basically, go to the nearest ancestor for which given node will be in the left subtree.

Problem: How do we go to the parent of the node that we visited to go to the nearest ancestor?
Fix: Add one more field called 'parent' to the node structure to store the address of the parent.
     But if there is no link to the parent, we can start at the root and walk the tree from the tree to the given node. We have to find the deepest ancestor for which the given node is in the left subtree.   

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* GetNewNode(int data);
Node* Insert(Node* rootPtr, int data);
void InorderTraversal(Node* rootPtr);

Node* GetSuccessor(Node* rootPtr, int data); // Returns address of the successor node.
/* We can also do Node* GetSuccessor(Node* rootPtr, Node* current) which just means that we take the address of the node what we want to find the successor to instead of the data in the 'data' field. 

We can also set the return type of the function as int if we want to directly return the inorder succesor instead of returning the address of the successor node.*/

Node* Find(Node* rootPtr, int data); // Helper function; find the target node
Node* FindMin(Node* rootPtr); // Helper function; find smallest element in the right subtree

int main() {
    Node* rootPtr = NULL;
    int n = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int data = 0;

        printf("Enter element #%d: ", i + 1);
        scanf("%d", &data);

        rootPtr = Insert(rootPtr, data);
    }

    int key = 0;

    printf("Enter the element whose inorder successor is to be found: ");
    scanf("%d", &key);

    Node* current = Find(rootPtr, key);

    if (current == NULL) {
        printf("Element was not found in the tree.\n");
    } else {
        Node* successor = GetSuccessor(rootPtr, key);

        if (successor == NULL) {
            printf("%d has no inorder successor.\n", key);
        } else {
            printf("Inorder successor of %d is %d.\n",
                   key, successor->data);
        }
    }

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

void InorderTraversal(Node* rootPtr) {
    if (rootPtr == NULL) return;
    InorderTraversal(rootPtr->left);
    printf("%d ", rootPtr->data);
    InorderTraversal(rootPtr->right);
}

Node* GetSuccessor(Node* rootPtr, int data) {
    // First, find the node
    Node* current = Find(rootPtr, data);
    if (current == NULL) {
        return NULL;
    }

    /*  CASE 1: Node has a right subtree. 
                Smallest value in the right subtree of the node. 
    */
    if (current->right != NULL) {
        return FindMin(current->right);
    } else {
        // CASE 2: Node doesn't have a right subtree
        Node* successor = NULL;
        Node* ancestor = rootPtr;
        while (ancestor != current) {
            if (current->data < ancestor->data) {
                successor = ancestor; // this is the deepest ancestor for which current node is in the left subtree
                ancestor = ancestor->left; 
            } else {
                ancestor = ancestor->right; // Visiting the parent from the right, so the parent is not the successor   
            }
        }
        return successor;
    }

}

Node* Find(Node* rootPtr, int data) {
    if (rootPtr == NULL) {
        return NULL;
    }
    
    if (rootPtr->data == data) {
        return rootPtr;
    } else if (rootPtr->data >= data) {
        return Find(rootPtr->left, data);
    } else {
        return Find(rootPtr->right, data);
    }
}

Node* FindMin(Node* rootPtr) {
    if (rootPtr == NULL) {
        return NULL;
    }

    while (rootPtr->left != NULL) {
        rootPtr = rootPtr->left;
    }

    return rootPtr;
}
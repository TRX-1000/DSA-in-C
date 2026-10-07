#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

int Precedence(char op);
int IsOperator(char ch);

void InfixToPostfix(char infix[], char postfix[]);

Node* GetNewNode(char data);
Node* BuildExpressionTree(char postfix[]);

void Inorder(Node* rootPtr);
void Preorder(Node* rootPtr);
void Postorder(Node* rootPtr);

void PrintTree(Node* rootPtr, int space);
void FreeTree(Node* rootPtr);


int main(void) {

    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    InfixToPostfix(infix, postfix);

    printf("\nPostfix expression: %s\n", postfix);

    Node* rootPtr = BuildExpressionTree(postfix);

    printf("\nInorder traversal: ");
    Inorder(rootPtr);

    printf("\nPreorder traversal: ");
    Preorder(rootPtr);

    printf("\nPostorder traversal: ");
    Postorder(rootPtr);

    printf("\n\nExpression Tree:\n");
    PrintTree(rootPtr, 0);


    FreeTree(rootPtr);

    return 0;
}

int Precedence(char op) {

    if (op == '+' || op == '-') {
        return 1;
    }

    if (op == '*' || op == '/') {
        return 2;
    }

    return 0;
}


int IsOperator(char ch) {

    return ch == '+' ||
           ch == '-' ||
           ch == '*' ||
           ch == '/';
}


void InfixToPostfix(char infix[], char postfix[]) {

    char stack[MAX];

    int top = -1;
    int i = 0;
    int j = 0;


    while (infix[i] != '\0') {

        /* Ignore spaces and newline */

        if (infix[i] == ' ' || infix[i] == '\n') {
            i++;
            continue;
        }


        /* Operand */

        if (isalnum(infix[i])) {

            postfix[j] = infix[i];

            j++;
        } else if (infix[i] == '(') {

            stack[++top] = infix[i];
        } else if (infix[i] == ')') {

            while (top != -1 &&
                   stack[top] != '(') {

                postfix[j++] = stack[top--];
            }

            /*
             * Remove '(' from stack
             */
            if (top != -1) {
                top--;
            }
        }


        /* Operator */

        else if (IsOperator(infix[i])) {

            while (top != -1 &&
                   stack[top] != '(' &&
                   Precedence(stack[top])
                   >= Precedence(infix[i])) {

                postfix[j++] = stack[top--];
            }

            stack[++top] = infix[i];
        }


        i++;
    }


    /* Pop remaining operators */

    while (top != -1) {

        postfix[j++] = stack[top--];
    }


    /* End postfix string */

    postfix[j] = '\0';
}


/* Create new tree node */

Node* GetNewNode(char data) {

    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = data;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


Node* BuildExpressionTree(char postfix[]) {

    Node* stack[MAX];

    int top = -1;
    int i = 0;


    while (postfix[i] != '\0') {


        /* Operand */

        if (isalnum(postfix[i])) {

            Node* newNode = GetNewNode(postfix[i]);

            stack[++top] = newNode;
        }


        /* Operator */

        else if (IsOperator(postfix[i])) {

            Node* newNode = GetNewNode(postfix[i]);


            // First pop = right child
            newNode->right = stack[top--];


            // Second pop = left child
            newNode->left = stack[top--];


            // Push root of newly created subtree
            stack[++top] = newNode;
        }

        i++;
    }


    // Final remaining node is root of complete expression tree
    return stack[top];
}

void Inorder(Node* rootPtr) {

    if (rootPtr == NULL) {
        return;
    }


    if (IsOperator(rootPtr->data)) {
        printf("(");
    }


    Inorder(rootPtr->left);

    printf("%c", rootPtr->data);

    Inorder(rootPtr->right);


    if (IsOperator(rootPtr->data)) {
        printf(")");
    }
}

void Preorder(Node* rootPtr) {

    if (rootPtr == NULL) {
        return;
    }

    printf("%c", rootPtr->data);

    Preorder(rootPtr->left);
    Preorder(rootPtr->right);
}

void Postorder(Node* rootPtr) {

    if (rootPtr == NULL) {
        return;
    }

    Postorder(rootPtr->left);
    Postorder(rootPtr->right);

    printf("%c", rootPtr->data);
}

void PrintTree(Node* rootPtr, int space) {

    if (rootPtr == NULL) {
        return;
    }

    space += 5;


    PrintTree(rootPtr->right, space);


    printf("\n");

    for (int i = 5; i < space; i++) {
        printf(" ");
    }

    printf("%c\n", rootPtr->data);


    PrintTree(rootPtr->left, space);
}

void FreeTree(Node* rootPtr) {

    if (rootPtr == NULL) {
        return;
    }

    FreeTree(rootPtr->left);
    FreeTree(rootPtr->right);

    free(rootPtr);
} 
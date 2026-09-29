#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

char stack[MAX];
int top = -1;

void Push(char symbol);
char Pop(void);
int isEmpty(void);
char CheckBalancedParentheses(char exp[]);

int main() {
    char expression[20];
    printf("Enter an expression containing multiple brackets: ");
    scanf(" %[^\n]", expression);

    top = -1; // reset stack between tests
    char result = CheckBalancedParentheses(expression);
    printf("%s -> %c\n", expression, result);

    return 0;
}

void Push(char symbol) {
    if (top == MAX - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack[++top] = symbol;
}

char Pop(void) {
    if (top == -1) {
        printf("Stack underflow, no elements to pop.\n");
        return '\0';
    }
    return stack[top--];
}

int isEmpty(void) {
    return (top == -1) ? 1 : 0;
}

char CheckBalancedParentheses(char exp[]) {
    int n = strlen(exp);
    for (int i = 0; i < n; i++) {
        if (exp[i] == '(' ||
            exp[i] == '[' ||
            exp[i] == '{' ||
            exp[i] == '<') {
            Push(exp[i]);
        } else if (exp[i] == ')' ||
                   exp[i] == ']' ||
                   exp[i] == '}' ||
                   exp[i] == '>') {
            if (isEmpty()) {
                printf("Closing bracket with nothing to match.\n");
                return 'N';
            }
            char top_symbol = Pop();
            if ((exp[i] == ')' && top_symbol != '(') ||
                (exp[i] == ']' && top_symbol != '[') ||
                (exp[i] == '}' && top_symbol != '{') ||
                (exp[i] == '>' && top_symbol != '<')) {
                printf("Mismatched pair: %c does not close %c.\n", exp[i], top_symbol);
                return 'N';
            }
        }
    }
    return isEmpty() ? 'Y' : 'N';
}

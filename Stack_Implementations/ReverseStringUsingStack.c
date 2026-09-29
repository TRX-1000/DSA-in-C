#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return '\0';
    }
    return stack[top--];
}

void reverseString(char *str) {
    int len = strlen(str);

    // Push all characters onto the stack
    for (int i = 0; i < len; i++) {
        push(str[i]);
    }

    // Pop them back into the string — reverses order
    for (int i = 0; i < len; i++) {
        str[i] = pop();
    }
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    scanf(" %[^\n]", str);

    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}

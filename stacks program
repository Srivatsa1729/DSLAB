#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure for stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an item to the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

// Function to return the top element of the stack
char peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return '$';
}

// Function to check if the given character is an operand
int isOperand(char ch) {
    return isalnum(ch);
}

// Function to return the precedence of the given operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char* infix, char* prefix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, j;
    j = 0;

    // Reverse the infix expression
    char temp;
    int len = strlen(infix);
    for (i = 0; i < len / 2; i++) {
        temp = infix[i];
        infix[i] = infix[len - i - 1];
        infix[len - i - 1] = temp;
    }

    // Iterate through infix expression
    for (i = 0; infix[i]; i++) {
        // If the scanned character is an operand, add it to the prefix expression
        if (isOperand(infix[i]))
            prefix[j++] = infix[i];
        // If the scanned character is a ')' push it to the stack
        else if (infix[i] == ')')
            push(stack, infix[i]);
        // If the scanned character is a '(' pop and add to the prefix expression until ')' is found
        else if (infix[i] == '(') {
            while (!isEmpty(stack) && peek(stack) != ')')
                prefix[j++] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != ')')
                return; // Invalid expression
            else
                pop(stack);
        }
        // If an operator is encountered
        else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                if (peek(stack) == '(')
                    return; // Invalid expression
                prefix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }

    // Pop all the operators from the stack
    while (!isEmpty(stack)) {
        if (peek(stack) == '(')
            return; // Invalid expression
        prefix[j++] = pop(stack);
    }

    // Reverse the prefix expression to get the final result
    prefix[j] = '\0';
    len = strlen(prefix);
    for (i = 0; i < len / 2; i++) {
        temp = prefix[i];
        prefix[i] = prefix[len - i - 1];
        prefix[len - i - 1] = temp;
    }

    // Deallocate memory
    free(stack->array);
    free(stack);
}

int main() {
    char infix[MAX_SIZE], prefix[MAX_SIZE];

    // Input infix expression from user
    printf("Enter an infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove trailing newline character

    // Convert infix to prefix
    infixToPrefix(infix, prefix);

    // Output the prefix expression
    printf("Prefix expression: %s\n", prefix);

    return 0;
}

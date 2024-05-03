#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure for stack
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an item to the stack
void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

// Function to evaluate postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(strlen(postfix));
    int i, operand1, operand2, result;

    // Iterate through the postfix expression
    for (i = 0; postfix[i]; i++) {
        // If the scanned character is an operand, push it to the stack
        if (isdigit(postfix[i]))
            push(stack, postfix[i] - '0');
        // If the scanned character is an operator, pop two operands from the stack, perform operation, and push the result back to the stack
        else {
            operand2 = pop(stack);
            operand1 = pop(stack);
            switch (postfix[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }
    // The final result is at the top of the stack
    result = pop(stack);

    // Deallocate memory
    free(stack->array);
    free(stack);

    return result;
}

int main() {
    char postfix[MAX_SIZE];

    // Input postfix expression from user
    printf("Enter a postfix expression: ");
    fgets(postfix, MAX_SIZE, stdin);
    postfix[strcspn(postfix, "\n")] = '\0';

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);


    printf("Result: %d\n", result);

    return 0;
}

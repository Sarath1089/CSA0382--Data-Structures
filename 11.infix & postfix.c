#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Stack implementation
struct Stack {
    int top;
    char items[MAX_SIZE];
};

void push(struct Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void infixToPostfix(const char* infix) {
    struct Stack stack;
    stack.top = -1;

    printf("Postfix expression: ");
    for (int i = 0; i < strlen(infix); ++i) {
        char ch = infix[i];
        if (isOperator(ch)) {
            while (stack.top != -1 && precedence(stack.items[stack.top]) >= precedence(ch)) {
                printf("%c", pop(&stack));
            }
            push(&stack, ch);
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (stack.top != -1 && stack.items[stack.top] != '(') {
                printf("%c", pop(&stack));
            }
            pop(&stack); // Discard '('
        } else {
            printf("%c", ch); // Operand
        }
    }

    while (stack.top != -1) {
        printf("%c", pop(&stack));
    }
    printf("\n");
}

int main() {
    const char* infixExpression = "3 + 4 * 5";
    infixToPostfix(infixExpression);
    return 0;
}

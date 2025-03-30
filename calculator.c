#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calculator.h"

// A stack to store numbers
typedef struct {
    double data[MAX];
    int top;
} Stack;

// A stack to store operators like +, -, *, /
typedef struct {
    char data[MAX];
    int top;
} CharStack;

// Add a number to the number stack
void push(Stack *s, double val) {
    s->data[++(s->top)] = val;
}

// Remove the top number from the number stack
double pop(Stack *s) {
    return s->data[(s->top)--];
}

// Add an operator to the operator stack
void pushChar(CharStack *s, char val) {
    s->data[++(s->top)] = val;
}

// Remove the top operator from the operator stack
char popChar(CharStack *s) {
    return s->data[(s->top)--];
}

// Check the top operator without removing it
char peekChar(CharStack *s) {
    return s->data[s->top];
}

// Check if the operator stack is empty
int isEmptyChar(CharStack *s) {
    return s->top == -1;
}

// Set priority for each operator
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Only ^ (power) is right to left
int isRightAssociative(char op) {
    return op == '^';
}

// Check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Change the infix expression to postfix (ex: (2+3)*4 → 2 3 + 4 *)
void infixToPostfix(char *infix, char postfix[][MAX], int *postfixSize) {
    CharStack opStack; opStack.top = -1;
    int i = 0, k = 0;

    while (infix[i]) {
        if (isspace(infix[i])) { i++; continue; }

        // Handle numbers and negative numbers
        if (isdigit(infix[i]) || (infix[i] == '-' && (i == 0 || infix[i-1] == '('))) {
            int j = 0;
            char num[MAX] = "";
            if (infix[i] == '-') num[j++] = infix[i++];
            while (isdigit(infix[i]) || infix[i] == '.') {
                num[j++] = infix[i++];
            }
            num[j] = '\0';
            strcpy(postfix[k++], num);
            continue;
        }

        // If character is (
        else if (infix[i] == '(') {
            pushChar(&opStack, infix[i]);
        }

        // If character is )
        else if (infix[i] == ')') {
            while (!isEmptyChar(&opStack) && peekChar(&opStack) != '(') {
                char op[2] = { popChar(&opStack), '\0' };
                strcpy(postfix[k++], op);
            }
            if (isEmptyChar(&opStack)) {
                printf("Error: Unmatched parentheses\n");
                exit(1);
            }
            popChar(&opStack); // remove (
        }

        // Handle +, -, *, /, ^ operators
        else if (isOperator(infix[i])) {
            while (!isEmptyChar(&opStack) &&
                   ((precedence(peekChar(&opStack)) > precedence(infix[i])) ||
                   (precedence(peekChar(&opStack)) == precedence(infix[i]) && !isRightAssociative(infix[i]))) &&
                   peekChar(&opStack) != '(') {
                char op[2] = { popChar(&opStack), '\0' };
                strcpy(postfix[k++], op);
            }
            pushChar(&opStack, infix[i]);
        }

        // Any invalid character
        else {
            printf("Error: Unknown symbol '%c'\n", infix[i]);
            exit(1);
        }
        i++;
    }

    // Add remaining operators to postfix
    while (!isEmptyChar(&opStack)) {
        if (peekChar(&opStack) == '(') {
            printf("Error: Unmatched parentheses\n");
            exit(1);
        }
        char op[2] = { popChar(&opStack), '\0' };
        strcpy(postfix[k++], op);
    }
    *postfixSize = k;
}

// Solve the postfix expression
double evaluatePostfix(char postfix[][MAX], int size) {
    Stack valStack; valStack.top = -1;

    for (int i = 0; i < size; i++) {
        // If it's an operator
        if (isOperator(postfix[i][0]) && strlen(postfix[i]) == 1) {
            if (valStack.top < 1) {
                printf("Error: Not enough numbers to calculate\n");
                exit(1);
            }
            double b = pop(&valStack);
            double a = pop(&valStack);
            char op = postfix[i][0];

            switch (op) {
                case '+': push(&valStack, a + b); break;
                case '-': push(&valStack, a - b); break;
                case '*': push(&valStack, a * b); break;
                case '/':
                    if (b == 0) {
                        printf("Error: You can't divide by zero\n");
                        exit(1);
                    }
                    push(&valStack, a / b); break;
                case '^': push(&valStack, pow(a, b)); break;
            }
        }
        // If it's a number
        else {
            push(&valStack, atof(postfix[i]));
        }
    }

    if (valStack.top != 0) {
        printf("Error: Something is wrong with the expression\n");
        exit(1);
    }

    return pop(&valStack);
}

// Ask user to continue
char askToContinue() {
    char ch;
    printf("Do you want to calculate again? (Y/N): ");
    scanf(" %c", &ch);
    while ((getchar()) != '\n');
    return ch;
}

// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#define MAX 100

// Declare the functions used in the calculator
void infixToPostfix(char *infix, char postfix[][MAX], int *postfixSize);
double evaluatePostfix(char postfix[][MAX], int size);
char askToContinue();

#endif
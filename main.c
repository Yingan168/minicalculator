#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main() {
    char input[256];             
    char postfix[MAX][MAX];      
    int size = 0;                
    char choice;                 // User choice to continue or not

    // Display welcome message
    printf("============================\n");
    printf(" Simple Expression Calculator\n");
    printf("============================\n");

    // Ask the user if they want to start
    choice = askToContinue();
    printf("============================\n");

    // Run the calculator as long as the user says yes
    while (choice == 'y' || choice == 'Y') {
        // Ask for a math expression
        printf("Please enter an expression: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline

        // Convert infix to postfix and calculate result
        infixToPostfix(input, postfix, &size);
        double answer = evaluatePostfix(postfix, size);

        // Show the result
        printf("Answer: %.6g\n", answer);
        printf("============================\n");

        // Ask if they want to try again
        choice = askToContinue();
        printf("============================\n");
    }

    // Exit message
    printf("Goodbye! Thanks for using the calculator.\n");
    printf("============================\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int numValidation (char input[]) {
    int validInput = 1;

    // Check each character in the input
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && input[i] != '.') {
            validInput = 0;
            printf("Invalid input! Please enter a number.\n");
            break;
        }
    }
    return validInput;
}
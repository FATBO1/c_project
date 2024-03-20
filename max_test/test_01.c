#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 10 // Maximum input length, excluding null terminator

int main() {
    char input[MAX_INPUT_LENGTH + 2]; // Buffer to hold user input (+2 for newline and null terminator)

    do {
        printf("Enter a string (up to %d characters): ", MAX_INPUT_LENGTH);
        fgets(input, sizeof(input), stdin); // Read user input

        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Check if input length is greater than MAX_INPUT_LENGTH
        if (strlen(input) > MAX_INPUT_LENGTH) {
            printf("Input exceeds maximum length! Please try again.\n");
        }
    } while (strlen(input) > MAX_INPUT_LENGTH); // Loop while input length is greater than MAX_INPUT_LENGTH

    printf("You entered: %s\n", input);

    return 0;
}

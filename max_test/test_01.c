#include <stdio.h>

int main() {
    int user_option;

    while (1) {
        // Print menu options
        printf("1. Save chart to text file.\n");
        printf("2. Modify chart.\n");
        printf("3. New Chart.\n");
        printf("4. Close Program.\n");
        printf("Enter your option: ");
        
        // Take user input
        scanf("%d", &user_option);
        getchar();  // Clearing the input buffer

        // Check user option
        switch (user_option) {
            case 1:
                // Code to save chart to text file
                printf("Saving chart to text file...\n");
                // You can put your saving code here
                break;
            case 2:
                // Code to modify chart
                printf("Modifying chart...\n");
                // You can put your modifying code here
                break;
            case 3:
                // Code to create new chart
                printf("Creating new chart...\n");
                // You can put your code for creating new chart here
                break;
            case 4:
                // Code to close the program
                printf("Closing program...\n");
                return 0; // Exit the program
            default:
                printf("Invalid option. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}

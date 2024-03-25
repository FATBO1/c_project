#include <stdbool.h>
#include <windows.h>

#ifndef coloured_bar_functions_H
#define coloured_bar_functions_H

WORD mapColourOptionToColour(int selection) {
    switch (selection) {
        case 1: return BACKGROUND_RED; //red
        case 2: return BACKGROUND_GREEN; //green
        case 3: return BACKGROUND_GREEN | BACKGROUND_BLUE; //cyan
        case 4: return BACKGROUND_BLUE; //blue
        case 5: return BACKGROUND_RED | BACKGROUND_GREEN; //yellow
        case 6: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; //white
        case 7: return BACKGROUND_RED | BACKGROUND_BLUE; //magenta
        case 8: return BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY; //pink
        case 9: return BACKGROUND_BLUE | BACKGROUND_INTENSITY; //light Blue
        case 10: return BACKGROUND_GREEN | BACKGROUND_INTENSITY; //light Green
        case 11: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; //light Yellow
        case 12: return BACKGROUND_RED | BACKGROUND_INTENSITY; //light Red
    }
}

void processCategorySelections(char input[], int num_categories, Category categories[], WORD colour) {
    // Arrays to hold valid and invalid inputs
    int validIndices[MAX_CATEGORIES];
    char invalidInputs[MAX_CATEGORIES][256]; // Assuming input will not exceed 256 characters for each
    int validCount = 0, invalidCount = 0;

    // Tokenize the input and process each category number
    char *category = strtok(input, ",");
    while (category != NULL) {
        int categoryIndex = atoi(category) - 1; // Convert the char to integer and -1 because category index start from 0

        // Input validation
        if (categoryIndex >= 0 && categoryIndex < num_categories) {
            // Store valid index
            if (validCount < MAX_CATEGORIES) {
                validIndices[validCount++] = categoryIndex;
            }
        } else {
            // Store invalid input for reporting
            if (invalidCount < MAX_CATEGORIES) {
                strncpy(invalidInputs[invalidCount++], category, 255);
                invalidInputs[invalidCount - 1][255] = '\0'; // Ensure null-termination
            }
        }

        category = strtok(NULL, ","); // get next input
    }

    // For each of the validIndices, set the colour for that category
    for (int i = 0; i < validCount; i++) {
        categories[validIndices[i]].colour = colour;
        printf("Category %s is set to color %d.\n", categories[validIndices[i]].name, colour);
    }

    // Report invalid inputs
    if (invalidCount > 0) {
        printf("Invalid category numbers: ");
        for (int i = 0; i < invalidCount; i++) {
            printf("%s%s", invalidInputs[i], (i < invalidCount - 1) ? ", " : "\n");
        }
    }
}

void defaultColourConfig(Category categories[], int num_categories) {
    for (int i = 0; i < num_categories; i++) {
        categories[i].colour = BACKGROUND_RED | BACKGROUND_INTENSITY; // Set default color to 1 for each category
    }
}

void manualColourConfig(Category categories[], int num_categories) {
    bool done = false; // boolean flag to exit loop when user is wants to finish config (option 0)
    while (!done){// list of available colours
        printf("List of colours available:\n");
        printf("1. Red\n");
        printf("2. Green\n");
        printf("3. Cyan\n");
        printf("4. Blue\n");
        printf("5. Yellow\n");
        printf("6. White\n");
        printf("7. Magenta\n");
        printf("8. Pink\n");
        printf("9. Light Blue\n");
        printf("10. Light Green\n");
        printf("11. Light Yellow\n");
        printf("12. Light Red\n");
        printf("Enter '0' to finish configuration.\n");
        
        int colourOption;
        printf("Select an option (0-12): ");
        int validInput = scanf("%d", &colourOption);
        while (getchar() != '\n'); // clear the input buffer

        if (validInput == 1) { // Check if scanf successfully read an integer
            if (colourOption == 0) {
                printf("0");
                done = true; // Set done flag to true to exit loop
            } else if (colourOption >= 1 && colourOption <= 12) {
                printf("Color %d selected.\n", colourOption);
                WORD colour = mapColourOptionToColour(colourOption);
                // List out categories
                printf("Available categories:\n");
                for (int i = 0; i < num_categories; i++) {
                    printf("%d. %s\n", i + 1, categories[i].name);
                }
                
                // User can select multiple categories
                printf("Enter category number(s) separated by commas (e.g., 1,3,5): ");
                char input[50]; // Buffer for user input
                fgets(input, sizeof(input), stdin); // Read the entire line

                processCategorySelections(input, num_categories, categories, colour);

            } else {
                printf("Invalid color selection. Please try again.\n");
            }
        } else {
            printf("Invalid Input. Please enter a number.\n");
        }
    }
    
}

#endif




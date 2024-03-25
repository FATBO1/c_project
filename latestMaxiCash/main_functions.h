#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h"
#include "compare_categories.h"
#include "validation.h"
#include "coloured_bar_functions.h"

void getCategories(char catInput[], int *num_categories) {
    do {
    printf("Enter the number of categories (up to 12): ");
    scanf(" %[^\n]", catInput);
    getchar(); // Clearing the input buffer

    int validInput = numValidation(catInput); // Input Validation

    // If input is valid (contains only digits), convert it to integer
    if (validInput)
    {
        *num_categories = atoi(catInput);
        if (*num_categories < 1 || *num_categories > 12)
        {
            printf("Enter a valid number between 1 and 12!\n");
        }
    }
    } while (*num_categories < 1 || *num_categories > 12);
}

void getCategoryInput(int *num_categories, Category *categories) {
    for (int i = 0; i < *num_categories; i++) {
        char input[100];
        do {
            // Input Category Name
            printf("Category %d name: ", i + 1);
            scanf(" %[^\n]", &input);
            getchar(); // Clearing the input buffer
            if (strlen(input) > MAX_CATEGORY_NAME_LENGTH)
            {
                printf("Category name is too long!\n");
            }
        } while (strlen(input) > 15 || strlen(input) == 0);
        strcpy(categories[i].name, input); // Copy value of input into typedef member name

        // Input Category Value
        char valueinput[100];
        int validInput = 0;

        do {
            printf("Value for %s: ", categories[i].name);
            scanf(" %[^\n]", valueinput);
            getchar(); // Clearing the input buffer
            validInput = 1;

            // Check each character in the input
            for (int j = 0; valueinput[j] != '\0'; j++) {
                if (!isdigit(valueinput[j]) && valueinput[j] != '.') {
                    validInput = 0;
                    printf("Invalid input! Please enter a number.\n");
                    break;
                }
            }

            if (validInput) {
                categories[i].value = atof(valueinput); // Convert input string to float
            }
        } while (!validInput);
    }
}

void sortCategories(char input[], int *sort_by_length, int *num_categories, Category *categories) {
    do {
        printf("Sort bars alphabetically by category name (0) or by bar length (1)? (0/1): ");
        scanf(" %[^\n]", input);
        getchar(); // Clearing the input buffer

        int validInput = numValidation(input); // Input Validation

        // If input is valid (contains only digits), convert it to integer
        if (validInput) {
            *sort_by_length = atoi(input);
            if (*sort_by_length == 0) {
                qsort(categories, *num_categories, sizeof(Category), compare_categories_by_name);
                break;
            }
            else if (*sort_by_length == 1) {
                qsort(categories, *num_categories, sizeof(Category), compare_categories_by_value);
                break;
            }
            else {
                printf("Invalid Choice.\n");
            }
        }
    } while (*sort_by_length != 0 || *sort_by_length != 1);
}

void colourConfigPrompt(int *userInput, int *num_categories, Category *categories) {
    do {
        printf("Default configurations(0) or Manually configure bar colour (1)? (0/1): ");
        int validInput = scanf("%d", userInput);
        while (getchar() != '\n'); // clear until buffer is empty so extra input wont be brought forward
        
        if (validInput == 1) {
            if (*userInput == 0) {
                defaultColourConfig(categories, *num_categories); //set all graph colour to default light red
                break; // Valid choice, exit loop
            } else if (*userInput == 1) {
                defaultColourConfig(categories, *num_categories); //set all graph colour to default light red
                manualColourConfig(categories, *num_categories); //let user customize graph colour (colour config menu)
                break; // Valid choice, exit loop
            } else {
                printf("Invalid Choice.\n");
            }
        } else {
            printf("Invalid Input.\n");
        }
    } while (*userInput != 0 || *userInput != 1); // Repeat until a valid input (0 or 1) is provided
}
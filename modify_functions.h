#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h"

void addCategory(int *num_categories, Category *categories) {
    // Add a category
    if (*num_categories < MAX_CATEGORIES) {
        char input[100];
        do {
            printf("\nEnter the name for the new category (max 15 characters each): ");
            scanf(" %[^\n]", &input);
            getchar(); // Clearing the input buffer
            if (strlen(input) > MAX_CATEGORY_NAME_LENGTH) {
                printf("Category name is too long!\n");
            }
        } while (strlen(input) > 15);
        strcpy(categories[*num_categories].name, input); // Copy value of input into typedef member name

        // Enter value for the new category
        char valueInput[100];
        int validInput = 0;
        do {
            printf("Value for %s: ", categories[*num_categories].name);
            scanf(" %[^\n]", valueInput);
            getchar(); // Clearing the input buffer
            
            int validInput = numValidation(valueInput); // Input Validation
            
            if (validInput) {
                categories[*num_categories].value = atof(valueInput); // Convert input string to float
                break;
            }
        } while (!validInput);
        
        (*num_categories)++; // Increment the count of categories
        printf("New category added successfully.\n");
        
    } else {
        printf("Cannot add more categories. Maximum categories reached.\n");
    }
}

void removeCategory(int *num_categories, Category *categories) {
    // Remove a category
    if (*num_categories > 0) {
        char input[100];
        int index;
        do {
            printf("\nEnter the index of the category you want to remove (1-%d): ", *num_categories);
            scanf(" %[^\n]", &input);
            getchar(); // Clearing the input buffer

            int validInput = numValidation(input);

            // If input is valid (contains only digits), convert it to integer
            if (validInput) {
                index = atoi(input);
                if (index >= 1 && index <= *num_categories) {
                    for (int i = index - 1; i < *num_categories - 1; i++) {
                        // Move category name and values forward to fill the empty space
                        strcpy(categories[i].name, categories[i + 1].name);
                        categories[i].value = categories[i + 1].value;
                    }
                    (*num_categories)--; // Decrement the count of categories
                    printf("Category %d removed successfully.\n", index);
                    break;
                } 
                else {
                    printf("Invalid category index. Please enter a valid index.\n");
                }
            }
        } while (index < 1 || index > *num_categories);
    } 
    else {
        printf("No categories to remove.\n");
    }
}

void modifyCategoryName(int *num_categories, Category *categories) {
    if (*num_categories > 0) {
        char input[100];
        int index;
        do {
            printf("\nEnter the index of the category you want to modify (1-%d): ", *num_categories);
            scanf(" %[^\n]", &input);
            getchar(); // Clearing the input buffer

            int validInput = numValidation(input); // Input Validation

            // If input is valid (contains only digits), convert it to integer
            if (validInput) {
                index = atoi(input);
                if (index >= 1 && index <= *num_categories) {
                    char input[100];
                    do {
                        printf("Enter the new name for category %d: ", index);
                        scanf(" %[^\n]", &input);
                        getchar(); // Clearing the input buffer
                        if (strlen(input) > MAX_CATEGORY_NAME_LENGTH) {
                            printf("Category name is too long!\n");
                        }
                    } while (strlen(input) > 15);
                    strcpy(categories[index - 1].name, input);
                    printf("Category %d name modified successfully.\n", index);
                }
                else {
                    printf("Invalid category index. Please enter a valid index.\n");
                }
            }
        } while (index < 1 || index > *num_categories);
        
    } else {
        printf("No categories to modify.\n");
    }
}

void modifyCategoryValue(int *num_categories, Category *categories) {
    if (*num_categories > 0) {
        char input[100];
        int index;
        do {
            printf("\nEnter the index of the category you want to modify (1-%d): ", *num_categories);
            scanf(" %[^\n]", &input);
            getchar(); // Clearing the input buffer

            int validInput = numValidation(input); // Input Validation

            // input is valid (contains only digits), convert it to integer
            if (validInput) {
                index = atoi(input);    
                if (index >= 1 && index <= *num_categories) {
                    char valueInput[100];
                    int validInput = 0;
                    do {
                        printf("Enter the new value for category %d: ", index);
                        scanf(" %[^\n]", valueInput);
                        getchar(); // Clearing the input buffer
                        
                        int validInput = numValidation(valueInput); // Input Validation

                        if (validInput) {
                            categories[index - 1].value = atof(valueInput);
                            break;
                        }
                    } while (!validInput);
                    
                    printf("Category %d value modified successfully.\n", index);
                    
                } 
                else {
                    printf("Invalid category index. Please enter a valid index.\n");
                }
            }
        } while (index < 1 || index > *num_categories);
    } 
    else {
        printf("No categories to modify.\n");
    }
}

void changeSort(int *num_categories, Category *categories) {
    char input[100];
    int sort_by_length;
    do {
        printf("Sort bars alphabetically by category name (0) or by bar length (1)? (0/1): ");
        scanf(" %[^\n]", input);
        getchar(); // Clearing the input buffer

        int validInput = numValidation(input); // Input Validation

        // If input is valid (contains only digits), convert it to integer
        if (validInput)
        {
            sort_by_length = atoi(input);
            if (sort_by_length == 0) {
                qsort(categories, *num_categories, sizeof(Category), compare_categories_by_name);
                printf("Sorting method changed successfully.\n");
                break;
            }
            else if (sort_by_length == 1) {
                qsort(categories, *num_categories, sizeof(Category), compare_categories_by_value);
                printf("Sorting method changed successfully.\n");
                break;
            }
            else {
                printf("Invalid Choice.\n");
            }
        }
    } while (sort_by_length != 0 || sort_by_length != 1);
}
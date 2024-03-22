#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "print_graph.h"
#include "save_graph.h"
#include "compare_categories.h"
#include "modify.h"
#include "import_excel.h"

int main()
{ 
    while (1)
    {
        char title[150];
        Category categories[MAX_CATEGORIES];
        char x_axis_label[150];
        int num_categories = 0;
        int i;
        int user_option;
        char filename[100];
        char filepath[260];
        

        // Gather information from the user
        printf("Enter the title of the bar chart: ");
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0'; // Removing newline character

        char catInput[100]; // Assuming input does not exceed 100 characters

        bool valid_Input = false; // Track validity of input
        while (!valid_Input) { //at the end of this while loop, if boolean variable "valid_Input" is false, means user did not input correctly, so code will run again
            printf("Would you like to (1) manually enter data or (2) import from a CSV file (only first 12 lines will be taken)? ");
            scanf("%d", &user_option);
            getchar(); // Clear the input buffer

        //read data from file
        if (user_option == 2) { 
            bool fileProcessed = false;
            while (!fileProcessed) { 
                printf("Enter the filepath of the CSV file or enter (1) to go back: ");
                scanf("%s", filepath);
                getchar(); // Clear the input buffer

                if (strcmp(filepath, "1") == 0) {
                    // User chooses to go back to previous menu
                    break;
                }

                fileProcessed = import_data_from_csv(filepath, categories, &num_categories);
                if (!fileProcessed) {
                    printf("Invalid file or file path. Please try again.\n");
                } else {
                    valid_Input = true; // Proceed with the next steps
                }
            }    
        }else if (user_option==1)
        {   
            valid_Input = true;
            do
            {
            printf("Enter the number of categories (up to 12): ");
            scanf(" %[^\n]", catInput);
            getchar(); // Clearing the input buffer

            int validInput = numValidation(catInput); // Input Validation

            // If input is valid (contains only digits), convert it to integer
            if (validInput)
            {
                num_categories = atoi(catInput);
                if (num_categories < 1 || num_categories > 12)
                {
                    printf("Enter a valid number between 1 and 12!\n");
                }
            }
            } while (num_categories < 1 || num_categories > 12);

            // Input Category Names and Values
            printf("Enter category names and values (max 15 characters each):\n");
            for (i = 0; i < num_categories; i++)
            {
                char input[100];
                do
                {
                    // Input Category Name
                    printf("Category %d name: ", i + 1);
                    scanf(" %[^\n]", &input);
                    getchar(); // Cleariteng the input buffer
                    if (strlen(input) > MAX_CATEGORY_NAME_LENGTH)
                    {
                        printf("Category name is too long!\n");
                    }
                } while (strlen(input) > 15 || strlen(input) == 0);
                strcpy(categories[i].name, input); // Copy value of input into typedef member name

                // Input Category Value
                char valueinput[100];
                int validInput = 0;

                do
                {
                    printf("Value for %s: ", categories[i].name);
                    scanf(" %[^\n]", valueinput);
                    getchar(); // Clearing the input buffer
                    validInput = 1;

                    // Check each character in the input
                    for (int j = 0; valueinput[j] != '\0'; j++)
                    {
                        if (!isdigit(valueinput[j]) && valueinput[j] != '.')
                        {
                            validInput = 0;
                            printf("Invalid input! Please enter a number.\n");
                            break;
                        }
                    }

                    if (validInput)
                    {
                        categories[i].value = atof(valueinput); // Convert input string to float
                    }
                } while (!validInput);
            }
            } else {
                printf("Invalid option. Please enter 1 or 2.\n");
                //if code enters here, means the boolean variable "valid_Input" still false, so code will go back to the start of while loop
                // and user will be prompted to choose again
            }
        }

        printf("Enter label for the x-axis: ");
        fgets(x_axis_label, sizeof(x_axis_label), stdin);
        x_axis_label[strcspn(x_axis_label, "\n")] = '\0'; // Removing newline character

        // Sort categories
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
                    qsort(categories, num_categories, sizeof(Category), compare_categories_by_name);
                    break;
                }
                else if (sort_by_length == 1) {
                    qsort(categories, num_categories, sizeof(Category), compare_categories_by_value);
                    break;
                }
                else {
                    printf("Invalid Choice.\n");
                }
            }
        } while (sort_by_length != 0 || sort_by_length != 1);

        // Print the horizontal bar chart
        print_horizontal_bar_chart(title, categories, num_categories, x_axis_label);

        while (1)
        {
            // Print menu options
            printf("\n1. Save chart to text file.\n");
            printf("2. Modify chart.\n");
            printf("3. New Chart.\n");
            printf("4. Close Program.\n");
            printf("Enter your option: ");

            // Take user input
            scanf("%d", &user_option);
            getchar(); // Clearing the input buffer

            // Check user option
            switch (user_option)
            {
            case 1:
                // Ask the user to enter the file name
                printf("Enter the file name: ");
                scanf("%s", filename);
                getchar(); // Clearing the input buffer

                // Check if the filename already ends with ".txt"
                if (strstr(filename, ".txt") == NULL)
                {
                    // If not, append ".txt" to the filename
                    strcat(filename, ".txt");
                }

                // Code to save chart to text file
                printf("\nSaving chart to text file...\n");

                // Open a file in write mode ("w")
                FILE *filePointer = fopen(filename, "w");
                // Check if the file was opened successfully

                if (filePointer == NULL)
                {
                    printf("Error opening the file.\n");
                    return 1; // Return an error code
                }
                print_horizontal_bar_chart_to_file(filePointer, title, categories, num_categories, x_axis_label);
                // Close the file
                fclose(filePointer);
                break;
            case 2:
                // Code to modify chart
                printf("\nModifying chart...\n");
                // You can put your modifying code here
                modify_chart(categories, &num_categories, title, x_axis_label, sort_by_length);
                print_horizontal_bar_chart(title, categories, num_categories, x_axis_label); // Print new chart
                break;
            case 3:
                // Code to create new chart
                printf("\nCreating new chart...\n");
                break;
            case 4:
                // Code to close the program
                printf("\nClosing program...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("\nInvalid option. Please enter a valid option.\n");
                break;
            }

            if (user_option == 3)
            {
                break; // Exit the inner loop on saving, closing program, or creating a new chart
            }
        }
    }

    return 0;
}

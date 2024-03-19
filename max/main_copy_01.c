#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "print_graph.h"
#include "save_graph.h"
#include "compare_categories.h"

int main()
{
    char title[150];
    Category categories[MAX_CATEGORIES];
    char x_axis_label[150];
    int sort_by_length;
    int num_categories, i;
    char save_chart_ans[4];

    // Gather information from the user
    printf("Enter the title of the bar chart: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; // Removing newline character

    char catinput[100]; // Assuming input does not exceed 100 characters
    do
    {
        printf("Enter the number of categories (up to 12): ");
        scanf("%s", catinput);
        getchar(); // Clearing the input buffer

        int validInput = 1;

        // Check each character in the input
        for (int i = 0; catinput[i] != '\0'; i++)
        {
            if (!isdigit(catinput[i]))
            {
                validInput = 0;
                printf("Invalid input! Please enter a number.\n");
                break;
            }
        }

        // If input is valid (contains only digits), convert it to integer
        if (validInput)
        {
            num_categories = atoi(catinput);
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
        char input[MAX_CATEGORY_NAME_LENGTH];
        do
        {
            // Input Category Name
            printf("Category %d name: ", i + 1);
            scanf("%s", &input);
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

        do
        {
            printf("Value for %s: ", categories[i].name);
            scanf("%s", valueinput);
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
    printf("Enter label for the x-axis: ");
    fgets(x_axis_label, sizeof(x_axis_label), stdin);
    x_axis_label[strcspn(x_axis_label, "\n")] = '\0'; // Removing newline character

    printf("Sort bars alphabetically by category name (0) or by bar length (1)? (0/1): ");
    scanf("%d", &sort_by_length);
    getchar(); // Clearing the input buffer

    // Sort categories
    if (sort_by_length)
    {
        qsort(categories, num_categories, sizeof(Category), compare_categories_by_value);
    }
    else
    {
        qsort(categories, num_categories, sizeof(Category), compare_categories_by_name);
    }

    // Print the horizontal bar chart
    print_horizontal_bar_chart(title, categories, num_categories, x_axis_label);

    printf("%s\n", "Do you want to save the chart? (yes/no):");
    fgets(save_chart_ans, sizeof(save_chart_ans), stdin);
    save_chart_ans[strcspn(save_chart_ans, "\n")] = '\0'; // Removing newline character
    if (strcmp(save_chart_ans, "yes") == 0)
    {
        // Open a file in write mode ("w")
        FILE *filePointer = fopen("saved_charts.txt", "w");
        // Check if the file was opened successfully
        if (filePointer == NULL)
        {
            printf("Error opening the file.\n");
            return 1; // Return an error code
        }
        print_horizontal_bar_chart_to_file(filePointer, title, categories, num_categories, x_axis_label);
        // Close the file
        fclose(filePointer);
        return 0; // Return success
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CATEGORIES 12
#define MAX_CATEGORY_NAME_LENGTH 15

typedef struct
{
    char name[MAX_CATEGORY_NAME_LENGTH + 1];
    float value;
} Category;

void print_horizontal_bar_chart(char title[], Category categories[], int num_categories, char x_axis_label[])
{
    int i, j;
    float max_value = 0;

    // Find the maximum value
    for (i = 0; i < num_categories; i++)
    {
        if (categories[i].value > max_value)
        {
            max_value = categories[i].value;
        }
    }

    // Scaling factor
    float scaling_factor = max_value > 134 ? max_value / 134 : 1;

    // Print the chart
    printf("\n");
    printf("%*s\n\n", 75 + strlen(title) / 2, title);

    for (i = 0; i < num_categories; i++)
    {
        printf("%15s|\n", " ");
        printf("%15s|", categories[i].name); // Print category name followed by a vertical bar
        int bar_length = categories[i].value / scaling_factor;
        for (j = 0; j < bar_length; ++j)
        {
            printf("X");
        }
        printf("\n");
    }
    printf("%15s|\n", " ");
    printf("%15s+", " ");

    // Print number of - before + to indicate tick marks
    for (int i = 0; i < 134; i++)
    {
        if (i == 49)
        {
            printf("+");
        }
        else if (i == 99)
        {
            printf("+");
        }
        else if (i > 135)
        {
            break;
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");

    // Print Tick Values
    if (scaling_factor != 1)
    {
        int tick1 = (max_value / 134) * 50;
        int tick2 = (max_value / 134) * 100;
        printf("%*s", 16, "0");
        printf("%*d", 50, tick1);
        printf("%*d\n\n", 50, tick2);
    }
    else
    {
        printf("%*s", 16, "0");
        printf("%*s", 50, "50");
        printf("%*s\n\n", 50, "100");
    }

    // Print X-Axis Label
    int label_padding = (150 - strlen(x_axis_label)) / 2;
    printf("%*s%s%*s\n\n", label_padding, "", x_axis_label, label_padding, "");

    // Save Chart (Incomplete)
    // printf("%s\n", "Do you want to save the chart? (yes/no): ");
}

void print_horizontal_bar_chart_to_file(FILE *filePointer, char title[], Category categories[], int num_categories, char x_axis_label[])
{
    int i, j;
    float max_value = 0;

    // Find the maximum value
    for (i = 0; i < num_categories; i++)
    {
        if (categories[i].value > max_value)
        {
            max_value = categories[i].value;
        }
    }

    // Scaling factor
    float scaling_factor = max_value > 134 ? max_value / 134 : 1;

    // Print the chart to the file
    fprintf(filePointer, "\n");
    fprintf(filePointer, "%*s\n\n", 75 + strlen(title) / 2, title);

    for (i = 0; i < num_categories; i++)
    {
        fprintf(filePointer, "%15s|\n", " ");
        fprintf(filePointer, "%15s|", categories[i].name); // Print category name followed by a vertical bar
        int bar_length = categories[i].value / scaling_factor;
        for (j = 0; j < bar_length; ++j)
        {
            fprintf(filePointer, "X");
        }
        fprintf(filePointer, "\n");
    }
    fprintf(filePointer, "%15s|\n", " ");
    fprintf(filePointer, "%15s+", " ");

    // Print number of - before + to indicate tick marks
    for (int i = 0; i < 134; i++)
    {
        if (i == 49)
        {
            fprintf(filePointer, "+");
        }
        else if (i == 99)
        {
            fprintf(filePointer, "+");
        }
        else if (i > 135)
        {
            break;
        }
        else
        {
            fprintf(filePointer, "-");
        }
    }
    fprintf(filePointer, "\n");

    // Print Tick Values
    if (scaling_factor != 1)
    {
        int tick1 = (max_value / 134) * 50;
        int tick2 = (max_value / 134) * 100;
        fprintf(filePointer, "%*s", 16, "0");
        fprintf(filePointer, "%*d", 50, tick1);
        fprintf(filePointer, "%*d\n\n", 50, tick2);
    }
    else
    {
        fprintf(filePointer, "%*s", 16, "0");
        fprintf(filePointer, "%*s", 50, "50");
        fprintf(filePointer, "%*s\n\n", 50, "100");
    }

    // Print X-Axis Label
    int label_padding = (150 - strlen(x_axis_label)) / 2;
    fprintf(filePointer, "%*s%s%*s\n\n", label_padding, "", x_axis_label, label_padding, "");
}

// Comparator function for sorting categories alphabetically by name
int compare_categories_by_name(const void *a, const void *b)
{
    return strcmp(((Category *)a)->name, ((Category *)b)->name);
}

// Comparator function for sorting categories by value (bar length)
int compare_categories_by_value(const void *a, const void *b)
{
    return (int)(((Category *)b)->value - ((Category *)a)->value);
}

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

    do
    {
        printf("Enter the number of categories (up to 12): ");
        scanf("%d", &num_categories);
        getchar(); // Clearing the input buffer
        if (num_categories < 1 || num_categories > 12)
        {
            printf("Enter a valid number!\n");
        }
    } while (num_categories < 1 || num_categories > 12);

    printf("Enter category names and values (max 15 characters each):\n");
    for (i = 0; i < num_categories; i++)
    {
        char input[MAX_CATEGORY_NAME_LENGTH];
        do
        {
            printf("Category %d name: ", i + 1);
            scanf("%s", &input);
            getchar(); // Clearing the input buffer
            if (strlen(input) > MAX_CATEGORY_NAME_LENGTH)
            {
                printf("Category name is too long!\n");
            }
        } while (strlen(input) > 15 || strlen(input) == 0);
        strcpy(categories[i].name, input); // Copy value of input into typedef member name

        printf("Value for %s: ", categories[i].name);
        scanf("%f", &categories[i].value);
        getchar(); // Clearing the input buffer
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
        FILE *filePointer = fopen("example.txt", "w");
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

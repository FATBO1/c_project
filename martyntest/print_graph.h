#ifndef print_horizontal_bar_chart_H
#define print_horizontal_bar_chart_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h> // Include necessary header for Windows-specific functions

#include "category.h" // Include the header file for Category struct definition
#include "coloured_bar.h" // Include the header file for coloured bar printing function


// Function to print a horizontal bar chart
void print_horizontal_bar_chart(char title[], Category categories[], int num_categories, char x_axis_label[])
{
    int i, j;
    float max_value = 0; // Variable to store the maximum value among all categories

    // Find the maximum value among all categories
    for (i = 0; i < num_categories; i++)
    {
        if (categories[i].value > max_value)
        {
            max_value = categories[i].value;
        }
    }

    // Determine the scaling factor to fit the bars within the display width
    float scaling_factor = max_value > 134 ? max_value / 134 : 1;

    // Print the chart
    printf("\n");
    printf("%*s\n\n", 75 + strlen(title) / 2, title);

    // Get console information for handling colors using Windows Console API
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes_first = consoleInfo.wAttributes;

    // Define attributes for white text on black background
    WORD whiteForegroundBlackBackground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // White text

    for (i = 0; i < num_categories; i++)
    {
        printf("%15s|\n", " "); // Print space and vertical bar for alignment
        printf("%15s|", categories[i].name); // Print category name followed by a vertical bar
        int bar_length = categories[i].value / scaling_factor; // Calculate the length of the bar based on the scaling factor
        
        // Print colored bar representing the category value
        printColoredBar(bar_length, BACKGROUND_RED | BACKGROUND_INTENSITY);
        
        // Reset text color to white after printing the bar
        SetConsoleTextAttribute(hConsole, whiteForegroundBlackBackground);

        // Print the numerical value of the category
        printf(" %.2f\n", categories[i].value);
    }

    // Print separator line after all bars
    printf("%15s|\n", " ");
    printf("%15s+", " ");

    // Print tick marks to indicate scale on the X-axis
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

    // Print tick values if scaling factor is applied
    if (scaling_factor != 1)
    {
        int tick1 = (max_value / 134) * 50;
        int tick2 = (max_value / 134) * 100;
        printf("%*s", 16, "0");
        printf("%*d", 50, tick1);
        printf("%*d\n\n", 50, tick2);
    }
    else // If no scaling factor, print default tick values
    {
        printf("%*s", 16, "0");
        printf("%*s", 50, "50");
        printf("%*s\n\n", 50, "100");
    }

    // Print X-axis label with appropriate padding for centering
    int label_padding = (150 - strlen(x_axis_label)) / 2;
    printf("%*s%s%*s\n\n", label_padding, "", x_axis_label, label_padding, "");
}

void print_vertical_bar_chart(char title[], Category categories[], int num_categories, char y_axis_label[])
{
    int i, j;
    float max_value = 0;

    // Find the maximum value among all categories
    for (i = 0; i < num_categories; i++)
    {
        if (categories[i].value > max_value)
        {
            max_value = categories[i].value;
        }
    }

    // Determine the scaling factor to fit the bars within the display height
    float scaling_factor = max_value > 20 ? max_value / 20 : 1;

    // Print the chart title
    printf("\n%*s\n\n", 40 + strlen(title) / 2, title);

    // Get console information for handling colors using Windows Console API
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes_first = consoleInfo.wAttributes;

    // Define attributes for white text on black background
    WORD whiteForegroundBlackBackground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    // Print the vertical axis labels
    for (float value = max_value; value >= 0; value -= max_value / 10)
    {
        printf("%6.2f |", value);
        for (i = 0; i < num_categories; i++)
        {
            if (categories[i].value >= value)
            {
                // Print colored bar using Windows Console API
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY);
                printf("  ██  ");
                SetConsoleTextAttribute(hConsole, whiteForegroundBlackBackground);
            }
            else
                printf("      ");
        }
        printf("\n");
    }

    // Print the horizontal axis labels
    printf("       +");
    for (i = 0; i < num_categories; i++)
    {
        printf("------");
    }
    printf("\n        ");
    for (i = 0; i < num_categories; i++)
    {
        printf(" %.*s ", 3, categories[i].name);
    }
    printf("\n");

    // Print Y-axis label with appropriate padding for centering
    int label_padding = (40 - strlen(y_axis_label)) / 2;
    printf("\n%*s%s%*s\n", label_padding, "", y_axis_label, label_padding, "");
}

#endif // End of header guard

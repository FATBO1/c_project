#ifndef print_bar_chart_H
#define print_bar_chart_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "category.h"
#include "coloured_bar.h"

// Function to print a horizontal bar chart
void print_horizontal_bar_chart(char title[], Category categories[], int num_categories, char x_axis_label[])
{
    // ... (existing code for horizontal bar chart) ...
}

// Function to print a vertical bar chart
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

    // Print the vertical axis labels
    for (float value = max_value; value >= 0; value -= max_value / 10)
    {
        printf("%6.2f |", value);
        for (i = 0; i < num_categories; i++)
        {
            if (categories[i].value >= value)
                printf("  ██  ");
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

#endif
#ifndef print_horizontal_bar_chart_to_file_H
#define print_horizontal_bar_chart_to_file_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h" // Include the header file for the Category struct definition


// Function to print a horizontal bar chart to a file
void print_horizontal_bar_chart_to_file(FILE *filePointer, char title[], Category categories[], int num_categories, char x_axis_label[])
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

    // Determine the scaling factor to fit the bars within the display width
    float scaling_factor = max_value > 134 ? max_value / 134 : 1;

    // Print the chart to the file
    fprintf(filePointer, "\n");

    // Print the chart title with appropriate padding
    fprintf(filePointer, "%*s\n\n", 75 + strlen(title) / 2, title); 

    for (i = 0; i < num_categories; i++)
    {
        fprintf(filePointer, "%15s|\n", " "); // Print space and vertical bar for alignment
        fprintf(filePointer, "%15s|", categories[i].name); // Print category name followed by a vertical bar
        int bar_length = categories[i].value / scaling_factor; // Calculate the length of the bar based on the scaling factor
        
        // Print bars representing the category value using Unicode block characters for better visualization
        for (j = 0; j < bar_length; ++j)
        {
            //fprintf(filePointer, "X");
            fprintf(filePointer, "█");
   
        }
        // Print the numerical value of the category
        fprintf(filePointer, " %.2f\n", categories[i].value);
    }

    // Print separator line after all bars
    fprintf(filePointer, "%15s|\n", " ");
    fprintf(filePointer, "%15s+", " ");

    // Print tick marks to indicate scale on the X-axis
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

    // Print tick values if scaling factor is applied
    if (scaling_factor != 1)
    {
        int tick1 = (max_value / 134) * 50;
        int tick2 = (max_value / 134) * 100;
        fprintf(filePointer, "%*s", 16, "0");
        fprintf(filePointer, "%*d", 50, tick1);
        fprintf(filePointer, "%*d\n\n", 50, tick2);
    }
    else // If no scaling factor, print default tick values
    {
        fprintf(filePointer, "%*s", 16, "0");
        fprintf(filePointer, "%*s", 50, "50");
        fprintf(filePointer, "%*s\n\n", 50, "100");
    }

    // Print X-axis label with appropriate padding for centering
    int label_padding = (150 - strlen(x_axis_label)) / 2;
    fprintf(filePointer, "%*s%s%*s\n\n", label_padding, "", x_axis_label, label_padding, "");
}

#endif // End of header guard

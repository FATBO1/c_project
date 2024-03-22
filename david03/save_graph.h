#ifndef print_horizontal_bar_chart_to_file_H
#define print_horizontal_bar_chart_to_file_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h"

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
            //fprintf(filePointer, "X");
            fprintf(filePointer, "█");
   
        }
        fprintf(filePointer, " %.2f\n", categories[i].value);
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

#endif

#ifndef print_horizontal_bar_chart_H
#define print_horizontal_bar_chart_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "category.h"
#include "coloured_bar.h"


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


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes_first = consoleInfo.wAttributes;
    // Extract the foreground color bits (0-3) and combine them with black background (bits 4-7 set to 0)
    WORD whiteForegroundBlackBackground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // White text

    for (i = 0; i < num_categories; i++)
    {
        printf("%15s|\n", " ");
        printf("%15s|", categories[i].name); // Print category name followed by a vertical bar
        int bar_length = categories[i].value / scaling_factor;
        
        printColoredBar(bar_length, BACKGROUND_RED | BACKGROUND_INTENSITY);
        SetConsoleTextAttribute(hConsole, whiteForegroundBlackBackground);
        printf(" %.2f\n", categories[i].value);
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
}

#endif
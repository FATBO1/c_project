#ifndef PRINT_PIE_CHART_H
#define PRINT_PIE_CHART_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "category.h"

void print_pie_chart(char title[], Category categories[], int num_categories) {
    int i;
    float total_value = 0;

    // Calculate the total value of all categories
    for (i = 0; i < num_categories; i++) {
        total_value += categories[i].value;
    }

    printf("\n%s\n\n", title);

    // Print the pie chart
    for (i = 0; i < num_categories; i++) {
        float percentage = (categories[i].value / total_value) * 100;
        int num_chars = (int)round(percentage / 2);

        printf("%15s (%.2f%%): ", categories[i].name, percentage);
        for (int j = 0; j < num_chars; j++) {
            printf("█");
        }
        printf("\n");
    }

    printf("\n");
}

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "category.h"
#include "math_functions.h"

void mathAnalysis(Category *categories, int *num_categories) {
    int option;
    while (1) {
        printf("\n[Analysis Options]\n");
        printf("1. Calculate Mean.\n");
        printf("2. Calculate Median.\n");
        printf("3. Calculate Mode.\n");
        printf("4. Calculate Variance.\n");
        printf("5. Calculate Standard Deviation.\n");
        printf("6. Back to main menu.\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        getchar(); // Clearing the input buffer

        switch (option) {
            case 1:
                double mean = calculateMean(categories, &*num_categories);
                printf("\nMean: %.2f\n", mean);
                break;

            case 2:
                double median = calculateMedian(categories, &*num_categories);
                printf("\nMedian: %.2f\n", median);
                break;

            case 3:
                calculateMode(categories, &*num_categories);
                break;

            case 4:
                double variance = calculateVariance(categories, &*num_categories);
                printf("\nVariance: %.2f\n", variance);
                break;

            case 5:
                double standardDeviation = sqrt(calculateVariance(categories, &*num_categories));
                printf("\nStandard Deviation: %.2f\n", standardDeviation);
                break;

            case 6:
                // Back to main menu
                return;

            default:
                printf("Invalid option. Please enter a valid option.\n");
                break;
        }
    }
}
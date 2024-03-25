#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h"

// Function to calculate mean
double calculateMean(Category *categories, int *num_categories) {
    double sum = 0;
        for (int i = 0; i < *num_categories; i++) {
            sum += categories[i].value;
        }
    return sum / *num_categories;
}

// Function to compare integers for qsort
int compareIntegers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate the median of an array of numbers
double calculateMedian(Category *categories, int *num_categories) {
    int arr[*num_categories];
    for (int i = 0; i < *num_categories; i++) {
        arr[i] = categories[i].value;
    }
    // Sort the array
    qsort(arr, *num_categories, sizeof(int), compareIntegers);

    // If the count of numbers is odd, return the middle value
    if (*num_categories % 2 != 0) {
        return arr[*num_categories / 2];
    }
    // If the count of numbers is even, return the average of the two middle values
    else {
        return (arr[(*num_categories - 1) / 2] + arr[*num_categories / 2]) / 2.0;
    }
}

// Function to calculate the mode
void calculateMode(Category *categories, int *num_categories) {
    int data[*num_categories];
    for (int i = 0; i < *num_categories; i++) {
        data[i] = categories[i].value;
    }

    // Find the maximum value in the array
    int max = data[0];
    for (int i = 1; i < *num_categories; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    // Dynamically allocate memory for the frequency array
    int *frequency = (int *)calloc(max + 1, sizeof(int));
    if (frequency == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Count frequencies
    for (int i = 0; i < *num_categories; i++) {
        frequency[data[i]]++;
    }

    // Find maximum frequency
    int maxFrequency = 0; // Variable to store the maximum frequency
    for (int i = 0; i <= max; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
        }
    }

    // Check if all frequencies are equal to the maximum frequency
    int allEqual = 1;
    for (int i = 0; i <= max; i++) {
        if (frequency[i] < maxFrequency && frequency[i] != 0) {
            allEqual = 0;
            break;
        }
    }

    // Print mode(s) or message if no mode exists
    if (allEqual) {
        printf("\nNo mode exists. All numbers appear the same number of times.\n");
    } else {
        printf("Mode(s): ");
        for (int i = 0; i <= max; i++) {
            if (frequency[i] == maxFrequency) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    // Free dynamically allocated memory
    free(frequency);
}

double calculateVariance(Category *categories, int *num_categories) {
    // Step 1: Calculate the mean
    double mean = calculateMean(categories, num_categories);

    // Step 2: Calculate the squared differences and sum them up
    double sumSquaredDiffs = 0.0;
    for (int i = 0; i < *num_categories; i++) {
        double diff = categories[i].value - mean;
        sumSquaredDiffs += diff * diff;
    }

    // Step 3: Calculate the mean of the squared differences (variance)
    double variance = sumSquaredDiffs / *num_categories;

    return variance;
}
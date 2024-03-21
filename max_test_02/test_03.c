#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CATEGORIES 5
#define CHART_WIDTH 50

typedef struct {
    char name[16];
    int value;
} Category;

// Sample data
Category categories[MAX_CATEGORIES] = {
    {"Apples", 5},
    {"Bananas", 10},
    {"Cherries", 7},
    {"Dates", 10},
    {"Elderberries", 15}
};

// Function prototypes
void renderChart(Category categories[], int numCategories, float scale);
int maxCategoryValue(Category categories[], int numCategories);

int main() {
    int input;
    float scale = 1.0; // Initial scale

    do {
        printf("Sales Figures 2024\n");
        printf("1. Zoom In\n");
        printf("2. Zoom Out\n");
        printf("3. Show Chart\n");
        printf("4. Quit\n");
        printf("Select an option: ");
        scanf("%d", &input);

        switch (input) {
            case 1: // Zoom In
                scale *= 0.5;
                break;
            case 2: // Zoom Out
                scale *= 2;
                break;
            case 3: // Show Chart
                system("clear"); // Use system("cls") on Windows
                renderChart(categories, MAX_CATEGORIES, scale);
                break;
            case 4: // Quit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (input != 4);

    return 0;
}

void renderChart(Category categories[], int numCategories, float scale) {
    int maxValue = maxCategoryValue(categories, numCategories);
    for (int i = 0; i < numCategories; i++) {
        int barLength = (int)((categories[i].value / (float)maxValue) * CHART_WIDTH * scale);
        printf("| %s ", categories[i].name);
        for (int j = 0; j < barLength; j++) {
            printf("X");
        }
        printf("\n");
    }
    // Simplified x-axis
    printf("+");
    for (int i = 0; i < CHART_WIDTH * scale; i++) {
        printf("-");
    }
    printf("\n");
}

int maxCategoryValue(Category categories[], int numCategories) {
    int maxValue = 0;
    for (int i = 0; i < numCategories; i++) {
        if (categories[i].value > maxValue) {
            maxValue = categories[i].value;
        }
    }
    return maxValue;
}

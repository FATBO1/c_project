#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 12
#define MAX_CATEGORY_NAME_LENGTH 15
#define MAX_TITLE_LENGTH 50
#define MAX_LABEL_LENGTH 20

typedef struct {
    char name[MAX_CATEGORY_NAME_LENGTH + 1];
    int value;
} Category;

void getInput(char *title, Category *categories, int *numCategories, char *xAxisLabel, int *sortOption);
void draw_horizontal_bar_chart(title, categories, numCategories, xAxisLabel, sortOption);

int main() {
    char title[MAX_TITLE_LENGTH + 1];
    Category categories[MAX_CATEGORIES];
    int numCategories = 0;
    char xAxisLabel[MAX_LABEL_LENGTH + 1];
    int sortOption;

    getInput(title, categories, &numCategories, xAxisLabel, &sortOption);
    displayBarChart(title, categories, numCategories, xAxisLabel, sortOption);

    return 0;
}

void getInput(char *title, Category *categories, int *numCategories, char *xAxisLabel, int *sortOption) {
    printf("Enter the title of the bar chart: ");
    fgets(title, MAX_TITLE_LENGTH + 1, stdin);
    title[strcspn(title, "\n")] = 0; // Remove newline character

    printf("Enter the number of categories (up to 12): ");
    scanf("%d", numCategories);
    getchar(); // Consume newline character

    for (int i = 0; i < *numCategories; i++) {
        printf("Enter category name (up to 15 characters): ");
        fgets(categories[i].name, MAX_CATEGORY_NAME_LENGTH + 1, stdin);
        categories[i].name[strcspn(categories[i].name, "\n")] = 0; // Remove newline character

        printf("Enter the value for category %s: ", categories[i].name);
        scanf("%d", &categories[i].value);
        getchar(); // Consume newline character
    }

    printf("Enter the label for the x-axis: ");
    fgets(xAxisLabel, MAX_LABEL_LENGTH + 1, stdin);
    xAxisLabel[strcspn(xAxisLabel, "\n")] = 0; // Remove newline character

    printf("Sort bars by category name (1) or by bar length (2)? ");
    scanf("%d", sortOption);
    getchar(); // Consume newline character
}

void displayBarChart(char *title, Category *categories, int numCategories, char *xAxisLabel, int sortOption) {
    // Implement the logic to display the bar chart based on the user's input
    // This is a placeholder for the actual implementation
    printf("Title: %s\n", title);
    printf("Number of Categories: %d\n", numCategories);
    printf("X-Axis Label: %s\n", xAxisLabel);
    printf("Sort Option: %d\n", sortOption);

    // Example of displaying categories
    printf("Categories:\n");
    for (int i = 0; i < numCategories; i++) {
        printf("%s: %d\n", categories[i].name, categories[i].value);
    }
}
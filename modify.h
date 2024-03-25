#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "modify_functions.h"
#include "print_graph.h"
#include "compare_categories.h"
#include "display_categories.h"
#include "coloured_bar_functions.h"

void modify_chart(Category *categories, int *num_categories, char title[], char x_axis_label[]) {
    int option;
    while (1) {
        printf("\n[Modification Options]\n");
        printf("1. Add a category.\n");
        printf("2. Remove a category.\n");
        printf("3. Modify a category name.\n");
        printf("4. Modify a category value.\n");
        printf("5. Change chart title.\n");
        printf("6. Change x-axis title.\n");
        printf("7. Change sorting method.\n");
        printf("8. Modify bar colour.\n");
        printf("9. Back to main menu.\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        getchar(); // Clearing the input buffer
        
        switch (option) {
            case 1:
                // Add a category
                addCategory(&*num_categories, categories);
                break;
                
            case 2:
                printCategories(&*num_categories, categories);
                // Remove a category
                removeCategory(&*num_categories, categories);
                break;
                
            case 3:
                printCategories(&*num_categories, categories);
                // Modify a category name
                modifyCategoryName(&*num_categories, categories);
                break;
                
            case 4:
                printCategories(&*num_categories, categories);
                // Modify a category value
                modifyCategoryValue(&*num_categories, categories);
                break;
                
            case 5:
                // Change chart title
                printf("\nEnter the new title for the chart: ");
                scanf(" %[^\n]", title); // Read input including whitespace characters
                getchar(); // Clearing the input buffer
                printf("Chart title changed successfully.\n");
                break;
                
            case 6:
                // Change x-axis title
                printf("\nEnter the new label for the x-axis: ");
                scanf(" %[^\n]", x_axis_label); // Read input including whitespace characters
                getchar(); // Clearing the input buffer
                printf("X-axis label changed successfully.\n");
                break;

            case 7:
                // Change sorting method
                changeSort(&*num_categories, categories);
                break;
                
            case 8:
                // Colour configuration menu
                manualColourConfig(categories, *num_categories); //let user customize graph colour
                break;
            case 9:
                // Back to main menu
                return;
                
            default:
                printf("Invalid option. Please enter a valid option.\n");
                break;
        }
    }
}

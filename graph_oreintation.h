#ifndef graph_oreintation_H
#define graph_oreintation_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int chooseGraphOrientation() {
    int graphOrientation;

    while (1) {
        printf("\nChoose the graph orientation:\n");
        printf("1. Horizontal bar graph\n");
        printf("2. Vertical bar graph\n");
        printf("Enter your choice: ");
        scanf("%d", &graphOrientation);
        getchar(); // Clearing the input buffer

        if (graphOrientation == 1 || graphOrientation == 2) {
            break; // Valid choice; exit the loop
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    return graphOrientation;
}



#endif // End of header guard



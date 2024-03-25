#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "category.h"

void printCategories(int *num_categories, Category *categories) {
    printf("\nCategories:\n");
    for (int i = 0; i < *num_categories; i++) {
        printf("[%d] %s\n", (i + 1), categories[i].name);
    }
}
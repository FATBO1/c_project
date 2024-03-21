#ifndef CATEGORY_H
#define CATEGORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CATEGORIES 12
#define MAX_CATEGORY_NAME_LENGTH 15

typedef struct
{
    char name[MAX_CATEGORY_NAME_LENGTH + 1];
    float value;
} Category;

#endif // CATEGORY_H

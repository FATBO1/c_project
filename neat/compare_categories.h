#ifndef compare_categories_H
#define compare_categories_H
// Header guard to prevent multiple inclusion of this header file


// Comparator function for sorting categories alphabetically by name
int compare_categories_by_name(const void *a, const void *b)
{
    // Compare the names of two categories and return the result
    return strcmp(((Category *)a)->name, ((Category *)b)->name);
}

// Comparator function for sorting categories by value (bar length)
int compare_categories_by_value(const void *a, const void *b)
{
    // Compare the values of two categories and return the result
    // Sorting in descending order to arrange categories with higher values first
    return (int)(((Category *)b)->value - ((Category *)a)->value);
}


#endif // End of header guard
SAFEARR_DISPATCH
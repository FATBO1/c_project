#ifndef compare_categories_H
#define compare_categories_H



// Comparator function for sorting categories alphabetically by name
int compare_categories_by_name(const void *a, const void *b)
{
    return strcmp(((Category *)a)->name, ((Category *)b)->name);
}

// Comparator function for sorting categories by value (bar length)
int compare_categories_by_value(const void *a, const void *b)
{
    return (int)(((Category *)b)->value - ((Category *)a)->value);
}


#endif // 

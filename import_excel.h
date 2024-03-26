
#define import_excel_H

bool import_data_from_csv(const char *filepath, Category categories[], int *num_categories) {
    // Check if the file has a .csv extension
    const char *dot = strrchr(filepath, '.');
    if (!dot || (strcmp(dot, ".csv") != 0 && strcmp(dot, ".CSV") != 0)) {
        printf("Wrong file type. Please ensure the file is a CSV file.\n");
        return false;
    }

    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to open file\n");
        return false;
    }
    
    char buffer[256];
    int count = -1;
   
    while (fgets(buffer, sizeof(buffer), file) && count < MAX_CATEGORIES) {
        // Assuming CSV format is: categoryName,value
        char *token = strtok(buffer, ",");
        strncpy(categories[count].name, token, MAX_CATEGORY_NAME_LENGTH);
        categories[count].name[MAX_CATEGORY_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
        token = strtok(NULL, ",");
        if (token) {
            categories[count].value = atof(token);
            count++;
        }
    }
    *num_categories = count;
    fclose(file);
    return true;
}
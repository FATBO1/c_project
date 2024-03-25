#define export_excel_H


void prompt_for_folder_path(char *folderPath, size_t size) {
    printf("Enter the folder path for the CSV export (if empty, current working directory will be used): ");
    fgets(folderPath, size, stdin);
    folderPath[strcspn(folderPath, "\n")] = '\0'; // Remove newline character
}

void construct_file_path(char *fullPath, const char *folderPath, const char *title, size_t size) {
    // Check if the folder path ends with a path separator ('/')
    size_t folderPathLen = strlen(folderPath);
    if (folderPathLen > 0 && (folderPath[folderPathLen - 1] == '/' || folderPath[folderPathLen - 1] == '\\')) {
        // If folderPath ends with '/', no need to add another '/'
        snprintf(fullPath, size, "%s%s.csv", folderPath, title);
    } else if (folderPathLen > 0) {
        // If folderPath does not end with '/', add it
        snprintf(fullPath, size, "%s/%s.csv", folderPath, title);
    } else {
        // If folderPath is empty, use the title directly in the current directory
        snprintf(fullPath, size, "%s.csv", title);
    }
}

void export_to_csv(const char *filepath, Category categories[], int num_categories) {
    // Check if the file already exists
    if (access(filepath, F_OK) == 0) {
        // File exists
        printf("File %s already exists. Do you want to overwrite it? (y/n): ", filepath);
        char response[3]; // Enough for y/n and newline character
        fgets(response, sizeof(response), stdin);

        // Clear the stdin buffer after reading the response, clear buffer so that the user input wont carry on to the following codes
        // else if the user enter too long of an input, the input will remain in the buffer cus fget takes in 3 only
        // so the remaining is brought forward in the code
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        // Check response using the first character
        if (response[0] != 'y' && response[0] != 'Y') {
            printf("Export cancelled by user.\n");
            return;
        }
    }

    FILE *file = fopen(filepath, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "Category,Value\n"); // Optional: Write header
    for (int i = 0; i < num_categories; i++) {
        fprintf(file, "%s,%f\n", categories[i].name, categories[i].value);
    }

    fclose(file);
    printf("Data exported to %s successfully.\n", filepath);
}

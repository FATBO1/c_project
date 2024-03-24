#include <stdio.h>
#include <stdlib.h>

char* readFileIntoString(const char *filePath) {
    FILE *file;
    char *buffer;
    long fileLen;

    // Open file
    file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file %s.\n", filePath);
        return NULL;
    }

    // Get file length
    fseek(file, 0, SEEK_END);
    fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents + null terminator
    buffer = (char *)malloc(fileLen + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Read file contents into buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    // Null-terminate the string
    buffer[fileLen] = '\0';

    return buffer;
}

int main() {
    char *fileContents = readFileIntoString("save.txt");
    if (fileContents != NULL) {
        printf("%s\n", fileContents);
        free(fileContents); // Free the memory when done
    } else {
        printf("Failed to read file.\n");
    }

    return 0;
}

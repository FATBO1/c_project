#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Driver code
int main()
{
    char save_chart_ans[4];
    printf("%s\n", "Do you want to save the chart? (yes/no): ");
    fgets(save_chart_ans, sizeof(save_chart_ans), stdin);
    save_chart_ans[strcspn(save_chart_ans, "\n")] = '\0'; // Removing newline character
    if (strcmp(save_chart_ans, "yes") == 0)
    {
        // Open a file in write mode ("w")
        FILE *filePointer = fopen("example.txt", "w");
        // Check if the file was opened successfully
        if (filePointer == NULL)
        {
            printf("Error opening the file.\n");
            return 1; // Return an error code
        }
        // Use fprintf to write formatted data to the file
        fprintf(filePointer, "Hello, fprintf!\n");
        // Close the file
        fclose(filePointer);
        return 0; // Return success
    }

    return 0;
}

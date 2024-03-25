#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include "main_functions.h"       // Custom header files for main functionalities
#include "print_graph.h"          // Handling printing of graphs
#include "save_graph.h"           // Handling saving graphs to files
#include "compare_categories.h"   // For comparing and sorting categories
#include "modify.h"               // For modifications of the charts
#include "import_excel.h"         // For importing data from excel/csv
#include "export_excel.h"         // For exporting data to excel/csv
#include "mathAnalysis.h"         // For obtaining values useful for statistical analysis
#include "gpt_api.h"
#include "ignore_check_libcurl.h"
#include "download_gcc_with_libcurl.h"



int main()
{ 
    
    while (1) // Main loop to continuously run the program until the user decides to exit
    {
        // Declaration of variables used throughout the program
        char title[150];                           // For storing chart title
        Category categories[MAX_CATEGORIES];       // Array of categories for the chart
        char x_axis_label[150];                    // For storing the X-axis label
        int num_categories = 0;                    // To keep track of the number of categories input by the user
        int user_option;                           // For storing user's choice from the menu
        char filename[100];                        // For storing filename when saving
        char filepath[260];                        // For storing file path for importing/exporting data
        char folderpath[260];                      // For storing folder path for exporting data
        

        // User input section for chart details
        printf("Enter the title of the bar chart: ");
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0'; // Removing newline character

        char catInput[100]; // Assuming input does not exceed 100 characters

        // Track validity of input
        bool valid_Input = false; 
        //at the end of this while loop, if boolean variable "valid_Input" is false, means user did not input correctly, so code will run again
        while (!valid_Input) { 
            printf("Would you like to (1) manually enter data or (2) import from a CSV file (only first 12 lines will be taken)? ");
            scanf("%d", &user_option);
            while (getchar() != '\n'); // Clear the input buffer completely

        //Read data from importing CSV
        if (user_option == 2) { 
            bool fileProcessed = false;
            while (!fileProcessed) { 
                printf("Enter the filepath of the CSV file or enter (1) to go back: ");
                scanf("%s", filepath);
                while (getchar() != '\n'); // Clear the input buffer completely

                if (strcmp(filepath, "1") == 0) {
                    // User chooses to go back to previous menu
                    break;
                }

                fileProcessed = import_data_from_csv(filepath, categories, &num_categories);
                if (!fileProcessed) {
                    printf("Invalid file or file path. Please try again.\n");
                } else {
                    // Proceed with the next steps
                    valid_Input = true; 
                }
            }    
        }else if (user_option==1)
        {   
            valid_Input = true;
            
            getCategories(catInput, &num_categories); // Prompt user for number of categories

            // Input Category Names and Values
            printf("Enter category names and values (max 15 characters each):\n");
            
            getCategoryInput(&num_categories, categories); // Prompt user for category name and value

            } else {
                printf("Invalid option. Please enter 1 or 2.\n");
                //if code enters here, means the boolean variable "valid_Input" still false, so code will go back to the start of while loop
                // and user will be prompted to choose again
            }
        }

        // Prompt user for x-axis label
        printf("Enter label for the x-axis: ");
        fgets(x_axis_label, sizeof(x_axis_label), stdin);
        x_axis_label[strcspn(x_axis_label, "\n")] = '\0'; // Removing newline character

        // Sort categories
        char input[100];
        int sort_by_length;
        sortCategories(input, &sort_by_length, &num_categories, categories); // Prompt user to sort categories by alphabet/value

        // Prompt user if they want to manually configure bar colour
        int userInput;
        colourConfigPrompt(&userInput, &num_categories, categories);

        int graph_orientation;
        while (1)
    {
        printf("\nChoose the graph orientation:\n");
        printf("1. Horizontal bar graph\n");
        printf("2. Vertical bar graph\n");
        printf("Enter your choice: ");
        scanf("%d", &graph_orientation);
        getchar(); // Clearing the input buffer

        if (graph_orientation == 1 || graph_orientation == 2)
        {
            break;
        }
        else
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    // Call the appropriate function based on the user's choice
    if (graph_orientation == 1)
    {
        print_horizontal_bar_chart(title, categories, num_categories, x_axis_label);
    }
    else
    {
        print_vertical_bar_chart(title, categories, num_categories, x_axis_label);
    }

        while (1)
        {
            // Print menu options
            printf("\n[Main Menu Options]\n");
            printf("1. Save chart to text file.\n");
            printf("2. Modify chart.\n");
            printf("3. New Chart.\n");
            printf("4. Export raw data to csv.\n");
            printf("5. Perform Statistical Analysis.\n");
            printf("6. Get analysis from ChatGPT API (gpt-3.5-turbo).\n");
            printf("7. Close Program.\n");
            printf("Enter your option: ");

            // Take user input for the options above
            scanf("%d", &user_option);
            getchar(); // Clearing the input buffer

            // Check user option
            switch (user_option)
            {
            case 1:
                // Ask the user to enter the file name
                printf("Enter the file name: ");
                scanf("%s", filename);
                getchar(); // Clearing the input buffer

                // Check if the filename already ends with ".txt"
                if (strstr(filename, ".txt") == NULL)
                {
                    // If not, append ".txt" to the filename
                    strcat(filename, ".txt");
                }

                // Code to save chart to text file
                printf("\nSaving chart to text file...\n");

                // Open a file in write mode ("w")
                FILE *filePointer = fopen(filename, "w");

                // Check if the file was opened successfully
                if (filePointer == NULL)
                {
                    printf("Error opening the file.\n");
                    return 1; // Return an error code
                }
                print_horizontal_bar_chart_to_file(filePointer, title, categories, num_categories, x_axis_label);
                
                // Close the file
                fclose(filePointer);
                break;

            case 2:
                // Code to modify chart
                printf("\nModifying chart...\n");

                // You can put your modifying code here
                modify_chart(categories, &num_categories, title, x_axis_label);
                print_horizontal_bar_chart(title, categories, num_categories, x_axis_label); // Print new chart
                break;

            case 3:
                // Code to create new chart
                printf("\nCreating new chart...\n");
                break;

            case 4:
                //code to export raw data
                prompt_for_folder_path(folderpath, sizeof(filepath));
                construct_file_path(filepath, folderpath, title, sizeof(filepath));
                export_to_csv(filepath, categories, num_categories);
                break;

            case 5:
                // Code to display analysis options menu
                printf("\nFetching Analysis Options...\n");
                mathAnalysis(categories, &num_categories);
                print_horizontal_bar_chart(title, categories, num_categories, x_axis_label); // Print chart
                break;

            case 6:
                printf("Enter the file name to analyze: ");
                scanf("%s", filename);
                getchar(); // Clearing the input buffer

                // Check if the filename already ends with ".txt"
                if (strstr(filename, ".txt") == NULL)
                {
                    // If not, append ".txt" to the filename
                    strcat(filename, ".txt");
                }
                printf("\n");
                if (send_get_GPT_response(filename)){
                    break;
                }
                break;

            case 7:
                // Code to close the program
                printf("\nClosing program...\n");
                exit(EXIT_SUCCESS);
                
            default:
                printf("\nInvalid option. Please enter a valid option.\n");
                break;
            }

            if (user_option == 3)
            {
                // Exit the inner loop on saving, closing program, or creating a new chart
                break; 
            }
        }
    }

    return 0;
}

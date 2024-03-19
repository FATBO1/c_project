char catinput[100]; // Assuming input does not exceed 100 characters
    do {
        printf("Enter the number of categories (up to 12): ");
        scanf("%s", catinput);

        int validInput = 1;

        // Check each character in the input
        for (int i = 0; catinput[i] != '\0'; i++) {
            if (!isdigit(catinput[i])) {
                validInput = 0;
                printf("Invalid input! Please enter a number.\n");
                break;
            }
        }

        // If input is valid (contains only digits), convert it to integer
        if (validInput) {
            num_categories = atoi(catinput);
            if (num_categories < 1  num_categories > 12) {
                printf("Enter a valid number between 1 and 12!\n");
            }
        }
    } while (num_categories < 1  num_categories > 12);
#include <windows.h>
#include <stdio.h>

void printColoredBar(int length, WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Save current attributes
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;

    // Set new color attributes
    SetConsoleTextAttribute(hConsole, color);

    // Print bar
    for (int i = 0; i < length; ++i) {
        printf(" "); // Print space with background color
    }
    printf("\n"); // New line after the bar

    // Reset to original attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}


int main() {
    // Save the current attributes
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;
    WORD whiteForegroundBlackBackground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // White text

    // Print a green bar with length 10
    printColoredBar(10, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    printf("\n"); // Extra newline for spacing, if needed

    // Print another green bar with length 50
    printColoredBar(50, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    printf("\n"); // Extra newline for spacing, if needed

    // Explicitly reset the console color to the original settings
    SetConsoleTextAttribute(hConsole, whiteForegroundBlackBackground);

    // Now the console color is back to default, as it was before calling printColoredBar
    printf("heyheyhey\n");

    int i;
    scanf("%d", &i); // Correct usage of scanf

    return 0;
}

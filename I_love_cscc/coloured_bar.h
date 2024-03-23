#ifndef coloured_bar_H
#define coloured_bar_H

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

    // Reset to original attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

#endif

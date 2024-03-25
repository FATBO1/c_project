#ifndef check_libcurl_H
#define check_libcurl_H

#include <windows.h>
#include <stdio.h>

int checkLibcurlInstalled() {
    // Attempt to load the libcurl DLL
    HMODULE hLibcurl = LoadLibrary(TEXT("libcurl.dll"));
    
    // Check if the DLL was loaded successfully
    if (hLibcurl == NULL) {
        printf("\nlibcurl is not installed.\n");
        return 0; // libcurl is not installed
    } else {
        printf("\nlibcurl is installed.\n");

        // Optionally, check for a specific function in the DLL
        FARPROC lpfnGetVersion = GetProcAddress(hLibcurl, "curl_version");
        if (!lpfnGetVersion) {
            printf("Specific libcurl function not found.\n");
        } else {
            printf("Specific libcurl function is available.\n");
        }
        
        // Clean up
        FreeLibrary(hLibcurl);
        return 1; // libcurl is installed
    }
}

/* int main() {
    checkLibcurlInstalled();
    return 0;
} */


#endif

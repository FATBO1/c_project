#include <windows.h>
#include <stdio.h>
#include "download_gcc_with_libcurl.h"

int checkLibcurlInstalled()
{
    // Attempt to load the libcurl DLL
    HMODULE hLibcurl = LoadLibrary(TEXT("libcurl.dll"));

    // Check if the DLL was loaded successfully
    if (hLibcurl == NULL)
    {
        printf("libcurl is not installed.\n");
        return 0; // libcurl is not installed
    }
    else
    {
        printf("libcurl is installed.\n");

        // Optionally, check for a specific function in the DLL
        FARPROC lpfnGetVersion = GetProcAddress(hLibcurl, "curl_version");
        if (!lpfnGetVersion)
        {
            printf("Specific libcurl function not found.\n");
        }
        else
        {
            printf("Specific libcurl function is available.\n");
        }

        // Clean up
        FreeLibrary(hLibcurl);
        return 1; // libcurl is installed
    }
}

int main()
{
    if (!checkLibcurlInstalled())
    {
        // printf("\n%s", "hey");
        int filesCopied = 0;
        const char *sourceFolderName = "msys64"; // Name of the source folder in the current directory
        const char *targetPath = "C:\\"; // Destination path where the source folder will be copied

        char currentDirectory[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, currentDirectory);

        char sourcePath[MAX_PATH];
        snprintf(sourcePath, MAX_PATH, "%s\\%s", currentDirectory, sourceFolderName);

        // Destination path is constructed by appending the source folder name to the target path
        char destinationPath[MAX_PATH];
        snprintf(destinationPath, MAX_PATH, "%s\\%s", targetPath, sourceFolderName);

        // Create the target directory if it doesn't exist
        if (!CreateDirectory(destinationPath, NULL))
        {
            DWORD lastError = GetLastError();
            // Check if the error is because the directory already exists
            if (lastError != ERROR_ALREADY_EXISTS)
            {
                printf("Unable to create directory %s. Error: %d\n", destinationPath, lastError);
                return 1; // Return an error code
            }
        }

        // Count the total number of files to copy
        int totalFiles = CountFilesInDirectory(sourcePath); // calling function from download_gcc_with_libcurl.h

        printf("\nCopying...\n");
        if (CopyFolderContents(sourcePath, destinationPath, &filesCopied, totalFiles))
        {                                               // calling function from download_gcc_with_libcurl.h
            UpdateProgressBar(filesCopied, totalFiles); // Final update to ensure progress bar reaches 100%, calling function from download_gcc_with_libcurl.h
            printf("\nFolder copied successfully.\n");
        }
        else
        {
            printf("\nFailed to copy folder.\n");
        }
    }
    return 0;
}

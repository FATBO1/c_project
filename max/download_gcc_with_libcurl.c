#include <windows.h>
#include <stdio.h>

// Function prototype for the file counting function
int CountFilesInDirectory(const char *directory);

void UpdateProgressBar(int currentStep, int totalSteps) {
    if (totalSteps <= 0) return; // To avoid division by zero

    int barWidth = 50; // Width of the progress bar in characters
    float progress = (float)currentStep / totalSteps;
    int pos = (int)(barWidth * progress);

    printf("\r[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d %%", (int)(progress * 100));
    fflush(stdout); // Ensure the progress bar is updated immediately
}

int CountFilesInDirectory(const char *directory) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    int fileCount = 0;

    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*", directory);
    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    } else {
        do {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    char nextDirPath[MAX_PATH];
                    snprintf(nextDirPath, MAX_PATH, "%s\\%s", directory, findFileData.cFileName);
                    fileCount += CountFilesInDirectory(nextDirPath);
                } else {
                    fileCount++;
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    return fileCount;
}

BOOL CopyFolderContents(const char *source, const char *destination, int *filesCopied, int totalFiles) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    BOOL retVal = TRUE;

    char srcSearchPath[MAX_PATH];
    snprintf(srcSearchPath, MAX_PATH, "%s\\*", source);
    hFind = FindFirstFile(srcSearchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("FindFirstFile failed (%d)\n", GetLastError());
        return FALSE;
    } else {
        do {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                char srcFilePath[MAX_PATH];
                char destFilePath[MAX_PATH];

                snprintf(srcFilePath, MAX_PATH, "%s\\%s", source, findFileData.cFileName);
                snprintf(destFilePath, MAX_PATH, "%s\\%s", destination, findFileData.cFileName);

                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    CreateDirectory(destFilePath, NULL); // Create the sub-directory in the destination
                    retVal = retVal && CopyFolderContents(srcFilePath, destFilePath, filesCopied, totalFiles);
                } else {
                    if (CopyFile(srcFilePath, destFilePath, FALSE)) {
                        (*filesCopied)++;
                        UpdateProgressBar(*filesCopied, totalFiles);
                    } else {
                        printf("\nFailed to copy file %s to %s (Error %d)\n", srcFilePath, destFilePath, GetLastError());
                        retVal = FALSE;
                    }
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0 && retVal);

        FindClose(hFind);
    }

    return retVal;
}

int main() {
    int filesCopied = 0;
    const char *sourceFolderName = "save"; // Name of the source folder in the current directory
    const char *targetPath = "C:\\"; // Destination path where the source folder will be copied

    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);

    char sourcePath[MAX_PATH];
    snprintf(sourcePath, MAX_PATH, "%s\\%s", currentDirectory, sourceFolderName);

    // Destination path is constructed by appending the source folder name to the target path
    char destinationPath[MAX_PATH];
    snprintf(destinationPath, MAX_PATH, "%s\\%s", targetPath, sourceFolderName);

    // Create the target directory if it doesn't exist
    if (!CreateDirectory(destinationPath, NULL)) {
        DWORD lastError = GetLastError();
        // Check if the error is because the directory already exists
        if (lastError != ERROR_ALREADY_EXISTS) {
            printf("Unable to create directory %s. Error: %d\n", destinationPath, lastError);
            return 1; // Return an error code
        }
    }

    // Count the total number of files to copy
    int totalFiles = CountFilesInDirectory(sourcePath);

    printf("Copying...\n");
    if (CopyFolderContents(sourcePath, destinationPath, &filesCopied, totalFiles)) {
        UpdateProgressBar(filesCopied, totalFiles); // Final update to ensure progress bar reaches 100%
        printf("\nFolder copied successfully.\n");
    } else {
        printf("\nFailed to copy folder.\n");
    }

    return 0;
}

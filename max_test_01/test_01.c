#include <stdio.h>
#include "curl/curl.h"
#include "cJSON.h"

#define BUFFER_SIZE 1024  // Adjust as necessary

// This function will be used as the callback function to write the received data
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Just print the received data to stdout
    fwrite(ptr, size, nmemb, stdout);
    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if(curl) {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, "http://google.com");

        // Set the callback function to handle the received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}
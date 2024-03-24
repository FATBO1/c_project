#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

#include "print_graph.h"          // Handling printing of graphs

#define JSON_MAX_LEN 2048


size_t write_callback( void *content, size_t size, size_t nmemb, void *userp ) {
    size_t total_size = size * nmemb;
    printf("%.*s", (int)nmemb, (char *)content );
    return total_size;
}

int main() {
    CURL *curl = curl_easy_init();

    if (curl == NULL) {
        fprintf(stderr, "Error: Unable to initialize Curl\n");
        return 1;
    }


    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers,  "Content-Type: application/json");
    headers = curl_slist_append(headers,  "Authorization: Bearer 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");
    

    char json_payload[JSON_MAX_LEN];
    sprintf( json_payload, "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"%s\"}]}", print_horizontal_bar_chart(title, categories, num_categories, x_axis_label) );

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    


    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK){
        fprintf(stderr, "ERROR: Unable to perform request: %s\n", curl_easy_strerror(res)); // Corrected fprintf usage
        return 1;
    }

    curl_easy_cleanup(curl);

    return 0;
}


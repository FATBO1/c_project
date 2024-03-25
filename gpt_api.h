#ifndef gpt_api_H
#define gpt_api_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

#include "cJSON/cJSON.h"
#include "read_textfile.h"
#include "escape_barchart.h"


#define JSON_MAX_LEN 4096 

size_t write_callback(void *content, size_t size, size_t nmemb, void *userp)
{
    size_t total_size = size * nmemb;
    char json_chunk[JSON_MAX_LEN] = "\0";
    sprintf(json_chunk, "%.*s", (int)nmemb, (char *)content);
    strcat((char *)userp, json_chunk);
    return total_size;
}


int send_get_GPT_response(char *filename) {
    CURL *curl = curl_easy_init();

    if (curl == NULL)
    {
        fprintf(stderr, "Error: Unable to initialize Curl\n");
        return 1;
    }

    char response[JSON_MAX_LEN] = "\0";

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer OpenAI_ChatGPT_KEY"); //OpenAI_ChatGPT_KEY

    // Read Bar Chart from saved text file
    char *bar_chart = readFileIntoString(filename); // call functionn from read_textfile.h
    if (bar_chart != NULL)
    {
        //printf("%s\n", bar_chart);
        printf("%s\n", "Sending bar chart to ChatGPT to analyze...\n");
    }
    else
    {
        printf("Failed to read file.\n");
        return 1;
    }

    char *prompt = "Base on the given bar chart provide some Visual Analysis, Statistical Analysis, Predictive Insights, Contextual Analysis, Trend Analysis, Comparative Analysis. Give an in depth and meaningful analysis on this bar chart. Give any predictions or any meaningful opinion.";
    char json_payload[JSON_MAX_LEN];
    sprintf(json_payload, "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"%s%s\"}]}", escape_barchart_forJSON(bar_chart), prompt);
    free(bar_chart); // Free the memory when done

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "ERROR: Unable to perform request: %s\n", curl_easy_strerror(res)); // Corrected fprintf usage
        return 1;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    //printf("%s\n", response); //print out entire json response from chatgpt API

    cJSON *root = cJSON_Parse(response);
    if (root == NULL)
    {
        fprintf(stderr, "ERROR: Unable to parse JSON: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    cJSON *choices = cJSON_GetObjectItem(root, "choices");
    if (choices == NULL)
    {
        fprintf(stderr, "ERROR: Unable to get choices: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    if (!cJSON_IsArray(choices))
    {
        fprintf(stderr, "ERROR: Choices is not an array\n");
        return 1;
    }

    cJSON *choice = cJSON_GetArrayItem(choices, 0);
    if (choice == NULL)
    {
        fprintf(stderr, "ERROR: Unable to get choice: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    if (!cJSON_IsObject(choice))
    {
        fprintf(stderr, "ERROR: Choices is not an object\n");
        return 1;
    }

    cJSON *message = cJSON_GetObjectItem(choice, "message");
    if (message == NULL)
    {
        fprintf(stderr, "ERROR: Unable to get message: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    if (!cJSON_IsObject(message))
    {
        fprintf(stderr, "ERROR: Choices is not an object\n");
        return 1;
    }

    cJSON *content = cJSON_GetObjectItem(message, "content");
    if (content == NULL)
    {
        fprintf(stderr, "ERROR: Unable to get content: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    if (!cJSON_IsString(content))
    {
        fprintf(stderr, "ERROR: Choices is not a string\n");
        return 1;
    }

    printf("%s\n", content->valuestring);
}

#endif // End of header guard

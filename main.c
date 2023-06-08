#include <stdio.h>
#include <curl/curl.h>
#include <string.h>


#define MAX_CONTENT_SIZE 4096

// Global variable to store the fetched content
char ver[MAX_CONTENT_SIZE] = "";
size_t ver_length = 0;

// Callback function to receive the fetched data
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;

    // Ensure enough space is available in ver
    if (ver_length + total_size >= MAX_CONTENT_SIZE - 1) {
        total_size = MAX_CONTENT_SIZE - 1 - ver_length;
    }

    // Copy the fetched data to ver
    memcpy(ver + ver_length, ptr, total_size);
    ver_length += total_size;

    // Null-terminate the string
    ver[ver_length] = '\0';

    return total_size;
}

// Function to retrieve the web page content and store it in the global variable
void fetch_web_page(const char *url) {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set the write callback function to handle the fetched data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup curl
        curl_easy_cleanup(curl);
    }

    // Print the fetched content
    printf("%s\n", ver);

    // Reset the data
    ver[0] = '\0';
    ver_length = 0;

    // Cleanup libcurl
    curl_global_cleanup();
}
int main() {
    char url[500];
    char command[1000];
 char oldurl[500];
 printf("Welcome to the official remote-shell cli | https://github.com/shourdev/rs-cli | API: {hosturl}/ex/ (GUIDE:https://github.com/shourdev/remote-shell#official-cli-client-) \n");
       printf("Enter the api url:");
    scanf("%s",oldurl);
    
    while (1){
   
    strcpy(url,oldurl);
 printf("Enter your command:");	
 scanf("%s",command);
 strcat(url,command);
  
fetch_web_page(url);


 
    }
}

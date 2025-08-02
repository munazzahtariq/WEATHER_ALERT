#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <unistd.h>  
#include"data.h"


#define HOURS 24

double temperatures[24] = { 0 };
double humidities[24] = { 0 };
char weather_descriptions[24][256] = { {0} };
char cities[24][256] = { {0} };
int data_count = 0;

size_t write_callback(void* contents, size_t size, size_t nmemb, char* userp) {
    size_t realsize = size * nmemb;
    strncat(userp, (char*)contents, realsize);  
    return realsize;
}

void fetch_data_from_api(const char* city, char* response) {
    CURL* curl;
    CURLcode res;
    char url[512];

    snprintf(url, sizeof(url), "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=6668d6e30eabcde8842b8f3c718920e3&units=metric", city);

    curl_global_init(CURL_GLOBAL_DEFAULT);  
    curl = curl_easy_init();  

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "CURL request failed: %s\n", curl_easy_strerror(res));
        }
        else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code != 200) {
                printf("Error: API returned status code %ld\n", response_code);
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    if (strlen(response) == 0) {
        printf("Error: Empty response from API.\n");
    }
}
void parse_weather_data(const char* response, int hour) {
    cJSON* json = cJSON_Parse(response);
    if (json == NULL) {
        printf("Error parsing JSON. Response:\n%s\n", response);  
        return;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* main = cJSON_GetObjectItemCaseSensitive(json, "main");
    cJSON* weather = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "weather"), 0);

    if (cJSON_IsObject(main)) {
        cJSON* temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
        cJSON* humidity = cJSON_GetObjectItemCaseSensitive(main, "humidity");

        if (cJSON_IsNumber(temp)) {
            temperatures[hour] = temp->valuedouble;
        }
        if (cJSON_IsNumber(humidity)) {
            humidities[hour] = humidity->valuedouble;
        }
    }

    if (cJSON_IsObject(weather)) {
        cJSON* description = cJSON_GetObjectItemCaseSensitive(weather, "description");
        if (cJSON_IsString(description) && (description->valuestring != NULL)) {
            snprintf(weather_descriptions[hour], sizeof(weather_descriptions[hour]), "%s", description->valuestring);
        }
    }

    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        snprintf(cities[hour], sizeof(cities[hour]), "%s", name->valuestring);
    }

    cJSON_Delete(json);
}

void calculate_average() {
    double total_temperature = 0;
    int valid_data_count = 0;

    for (int i = 0; i < HOURS; i++) {
        if (temperatures[i] != 0) {
            total_temperature += temperatures[i];
            valid_data_count++;
        }
    }

    if (valid_data_count > 0) {
        double average_temperature = total_temperature / valid_data_count;
        printf("Average Temperature: %.2f C\n", average_temperature);
    }
    else {
        printf("No valid temperature data to calculate average.\n");
    }
}

void display_hourly_data_and_average(const char* city) {
    char response[2048];

    for (int i = 0; i < HOURS; i++) {
        memset(response, 0, sizeof(response));  

        fetch_data_from_api(city, response);

        if (strlen(response) == 0) {
            printf("Error: No data received for hour %d\n", i + 1);
            continue;
        }

        parse_weather_data(response, i);

        printf("Hour %d:\n", i + 1);
        printf("City: %s\n", cities[i]);
        printf("Temperature: %.2f C\n", temperatures[i]);
        printf("Humidity: %.2f%%\n", humidities[i]);
        printf("Weather: %s\n\n", weather_descriptions[i]);

        if (i < HOURS - 1) {
            sleep(5);  
        }
    }

    calculate_average();
}










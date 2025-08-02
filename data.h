#ifndef DATA_H
#define DATA_H

extern double temperatures[24];
extern double humidities[24];
extern char weather_descriptions[24][256];
extern char cities[24][256];
extern int data_count;

void fetch_data_from_api(const char* city, char* response);
void parse_weather_data(const char* response, int hour);
void calculate_average();
void display_hourly_data_and_average(const char* city);

#endif 


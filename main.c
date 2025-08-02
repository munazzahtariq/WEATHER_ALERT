#include <stdio.h>
#include <stdlib.h>
#include "data.h"

extern double temperatures[24];
extern double humidities[24];
extern char weather_descriptions[24][256];
extern char cities[24][256];

int main() {
    const char* city = "Karachi";  
    display_hourly_data_and_average(city);

    return 0;
}


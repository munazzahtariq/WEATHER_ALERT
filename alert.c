#include "alert.h"
#include "data.h"
#include <stdio.h>


void check_and_generate_alerts(int hour) {
    if (temperatures[hour] > 30) {  
        char alert_message[256];
        snprintf(alert_message, sizeof(alert_message), "High temperature alert: %.2f°C", temperatures[hour]);
        send_alert(alert_message);
    }
    else if (humidities[hour] > 70) {  
        char alert_message[256];
        snprintf(alert_message, sizeof(alert_message), "High humidity alert: %.2f%%", humidities[hour]);
        send_alert(alert_message);
    }
}

void send_alert(const char* alert_message) {
    printf("ALERT: %s\n", alert_message);
}



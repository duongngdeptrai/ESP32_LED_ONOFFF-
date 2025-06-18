#include "wifi_manager.h"

void setup_wifi()
{
    delay(100);
    Serial.println("Đang kết nối WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }
    Serial.println();
    Serial.println("Đã kết nối WiFi!");
}

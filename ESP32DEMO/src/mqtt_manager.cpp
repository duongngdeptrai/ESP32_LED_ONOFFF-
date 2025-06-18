#include "mqtt_manager.h"
#include <Arduino.h>

void reconnect(PubSubClient &client, const char* mqtt_user, const char* mqtt_pass) {
  while (!client.connected()) {
    Serial.print("Đang kết nối MQTT...");

    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("Kết nối MQTT thành công!");
      client.subscribe("esp32/led");
      Serial.println("Đăng ký lắng nghe topic: esp32/led");

    } else {
      Serial.print("Thất bại, lỗi = ");
      Serial.print(client.state());
      Serial.println(" → thử lại sau 2 giây.");
      delay(2000);
    }
  }
}

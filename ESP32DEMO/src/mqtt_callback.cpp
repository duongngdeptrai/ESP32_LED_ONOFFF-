#include "mqtt_callback.h"
#include <Arduino.h>
#include <PubSubClient.h>

extern PubSubClient client; // khai báo để sử dụng được client từ nơi khác

const int ledPin = 2;

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Nhận thông điệp từ topic: ");
  Serial.println(topic);

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Nội dung: ");
  Serial.println(message);

  if (message == "on") {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED BẬT.");
    // Publish lại trạng thái
    client.publish("esp32/led/status", "on");

  } else if (message == "off") {
    digitalWrite(ledPin, LOW);
    Serial.println("LED TẮT.");
    // Publish lại trạng thái
    client.publish("esp32/led/status", "off");

  } else {
    Serial.println("Lệnh không xác định.");
  }
}

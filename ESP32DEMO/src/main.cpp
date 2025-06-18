#include <WiFi.h>               // Thư viện để ESP32 kết nối WiFi
#include <WiFiClientSecure.h>  // Thư viện khách hàng bảo mật, dùng để connect MQTT qua SSL/TLS
#include <PubSubClient.h>      // Thư viện PubSubClient để gửi/nhận tin MQTT

#include "wifi_manager.h"     // File khởi động WiFi
#include "mqtt_callback.h"   // File xử lý khi nhận được MQTT messages
#include "mqtt_manager.h"    // File reconnect nếu mất MQTT

// Thông tin cấu hình mạng
const char* ssid = "iPhone";
const char* password = "04022008";

// Thông tin cấu hình MQTT
const char* mqtt_server = "a5945d6121f349cfab40ce21deefd6dc.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "duong29";
const char* mqtt_pass = "Duongthcsvt2912";

// Chân GPIO để điều khiển LED
const int ledPin = 2;  

WiFiClientSecure espClient;
PubSubClient client(espClient); // PubSubClient cần một Client để gửi/nhận dữ liệu

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Tắt LED lúc khởi động

  setup_wifi();               // Kết nối vào mạng WiFi

  espClient.setInsecure();   // Bỏ qua kiểm tra chứng chỉ (đóng lúc phát triển hoặc test)

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback); // Hàm callback khi nhận được messages từ MQTT
}

void loop()
{
  if (!client.connected()) {
    reconnect(client, mqtt_user, mqtt_pass); // Nếu chưa connected, tự động reconnect
  }
  client.loop(); // Gọi hàm loop của client để xử lý các messages đến
  delay(10); 
}

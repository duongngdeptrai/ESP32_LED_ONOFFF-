#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Cấu hình WiFi và MQTT
const char* ssid = "Lucky House 6";
const char* password = "66668888";

const char* mqtt_server = "a5945d6121f349cfab40ce21deefd6dc.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "duong29";
const char* mqtt_password = "Duongthcsvt2912";

// Cấu hình chân LED
const int ledPin = 2;  // Chân D2 tương ứng GPIO 2 trên ESP32

WiFiClientSecure espClient;
PubSubClient client(espClient);

// Hàm xử lý khi nhận được tin nhắn MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📥 Nhận thông điệp từ topic: ");
  Serial.println(topic);

  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("🔹 Nội dung: ");
  Serial.println(message);

  if (message == "on") {
    digitalWrite(ledPin, HIGH);
    Serial.println("💡 LED BẬT");
  } else if (message == "off") {
    digitalWrite(ledPin, LOW);
    Serial.println("💤 LED TẮT");
  }
}

void setup_wifi() {
  delay(100);
  Serial.println("🔌 Đang kết nối WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Đã kết nối WiFi!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("🔄 Đang kết nối MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("✅ Kết nối MQTT thành công!");
      client.subscribe("esp32/led");  // 🔔 Subscribe topic để nhận lệnh
      Serial.println("📡 Đăng ký lắng nghe topic: esp32/led");
    } else {
      Serial.print("❌ Thất bại, lỗi = ");
      Serial.print(client.state());
      Serial.println(" → thử lại sau 2 giây");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Tắt LED ban đầu

  setup_wifi();
  espClient.setInsecure(); // Dùng nếu HiveMQ dùng chứng chỉ tự ký
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Gửi định kỳ test (không cần nếu bạn chỉ muốn nhận lệnh)
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 10000) {
    client.publish("esp32/test", "hello from ESP32");
    Serial.println("📤 Đã gửi test lên topic esp32/test");
    lastSend = millis();
  }
}

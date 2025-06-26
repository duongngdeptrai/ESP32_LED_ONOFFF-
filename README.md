💡 IoT LED Control using ESP32, MQTT, Node.js & Flutter

Một hệ thống IoT đơn giản cho phép bật/tắt đèn LED trên ESP32 thông qua ứng dụng Flutter và giao thức MQTT.


🧠 Tổng quan

Dự án gồm 3 phần chính:

ESP32: thiết bị phần cứng điều khiển đèn LED, giao tiếp MQTT.

Node.js Server: trung gian xử lý lệnh từ Flutter và chuyển tiếp tới ESP32 qua MQTT, đồng thời phát trạng thái về client qua SocketIO.

Flutter App: giao diện người dùng, cho phép bật/tắt đèn và nhận phản hồi trạng thái theo thời gian thực.


⚙️ Kiến trúc hệ thống

[Flutter App] <--> [Node.js Server] <--> [MQTT Broker] <--> [ESP32]

🔧 Thành phần sử dụng

ESP32: Lập trình bằng PlatformIO trên Visual Studio Code

MQTT Broker: HiveMQ Cloud

Node.js + Express + MQTT.js + Socket.IO

Flutter: Giao diện Android

const express = require("express");
const cors = require("cors");  
const mqtt = require("mqtt");  
const http = require("http");  
const { Server } = require("socket.io");  

const app = express();

app.use(cors());    
app.use(express.json());  

// Thông tin MQTT (điền theo tài khoản của bạn!)
const options = {
  host: "a5945d6121f349cfab40ce21deefd6dc.s1.eu.hivemq.cloud",
  port: 8883,
  protocol: "mqtts",
  username: "duong29",
  password: "Duongthcsvt2912",
};

const mqttClient = mqtt.connect(options);

// Kết nối MQTT
mqttClient.on("connect", () => {
  console.log("Đã connect MQTT.");
  // Đăng ký lắng nghe chủ đề từ ESP32 gửi về
  mqttClient.subscribe("esp32/led/status"); 
});

// Khi nhận được phản hồi từ ESP32
mqttClient.on("message", (topic, message) => {
  if (topic === "esp32/led/status") {
    console.log("Nhận từ ESP32 :", message.toString());

    // đẩy về Flutter qua socket
    io.emit("esp32-update", message.toString());  
  }
});

// API gửi lệnh từ Flutter xuống ESP32
app.post("/led", (req, res) => {
  const { command } = req.body;

  if (command !== "on" && command !== "off") {
    return res.status(400).send("Lệnh không hợp lệ.");
  }
  
  mqttClient.publish("esp32/led", command);
  console.log(`Đã gửi lệnh ${command} đến MQTT.`);
  res.send({ message: `Đã gửi lệnh ${command}` });
});

// Tích hợp socket
const server = http.createServer(app);
const io = new Server(server, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
  },
});

// socket connect
io.on("connection", (socket) => {
  console.log("Client Flutter connected.");
});

// khởi động
const port = 3000;
server.listen(port, () => {
  console.log(`Server tại http://localhost:${port}`);

});

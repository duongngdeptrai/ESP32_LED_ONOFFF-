const express = require("express");
const cors = require("cors");  // thêm cors
const mqtt = require("mqtt");

const app = express();

app.use(cors());              // bật CORS cho tất cả request
app.use(express.json());      // cho phép đọc JSON từ body

const options = {
  host: "a5945d6121f349cfab40ce21deefd6dc.s1.eu.hivemq.cloud",
  port: 8883,
  protocol: "mqtts",
  username: "duong29",
  password: "Duongthcsvt2912",
};

const client = mqtt.connect(options);

client.on("connect", () => {
  console.log("✅ Đã kết nối MQTT Broker HiveMQ");
});

app.post("/led", (req, res) => {
  const { command } = req.body;

  if (command !== "on" && command !== "off") {
    return res.status(400).send("❌ Lệnh không hợp lệ. Chỉ chấp nhận 'on' hoặc 'off'");
  }

  client.publish("esp32/led", command);
  console.log(`📤 Đã gửi lệnh "${command}" đến topic esp32/led`);
  res.send(`✅ Đã gửi lệnh ${command}`);
});

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`🚀 Server đang chạy tại http://localhost:${PORT}`);
});

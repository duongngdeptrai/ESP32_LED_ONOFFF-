import 'package:flutter/material.dart';
import 'package:socket_io_client/socket_io_client.dart' as IO;
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  MyAppState createState() => MyAppState();
}

class MyAppState extends State<MyApp> {
  late IO.Socket socket;
  bool isLedOn = false; // trạng thái đèn

  @override
  void initState() {
    super.initState();

    // Kết nối socket
    socket = IO.io('http://10.0.2.2:3000', <String, dynamic>{
      'transports': ['websocket'],
    });

    socket.on('connect', (_) {
      debugPrint('Đã connect socket');
    });

    // Khi nhận được dữ kiện "esp32-update" từ server
    socket.on('esp32-update', (data) {
      debugPrint('Nhận từ ESP32: $data');
      setState(() {
        isLedOn = (data == 'on'); // nếu server gửi "on" -> true, "off" -> false
      });
    });

    socket.on('disconnect', (_) {
      debugPrint('❕ Mất connect');
    });
  }

  Future<void> sendCommand(String command) async {
    try {
      final url = Uri.parse('http://10.0.2.2:3000/led');
      // Gửi yêu cầu POST đến server tại URL
      final response = await http.post(
        url,
        headers: {"Content-Type": "application/json"},
        body: json.encode({"command": command}),
      );

      if (response.statusCode == 200) {
        debugPrint('Đã gửi lệnh $command');
      } else {
        debugPrint('Lỗi gửi lệnh');
      }
    } catch (e) {
      debugPrint('Lỗi khi gửi lệnh: $e');
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: const Text('IoT - LED Control')),

        // Thân của ứng dụng
        body: Center(
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              Text(
                isLedOn ? "Đèn đang BẬT" : "Đèn đang TẮT",
                style: TextStyle(fontSize: 24),
              ),
              const SizedBox(height: 20),
              ElevatedButton(
                onPressed: () {
                  sendCommand("on");
                },
                child: const Text("Bật đèn"),
              ),
              ElevatedButton(
                onPressed: () {
                  sendCommand("off");
                },
                child: const Text("Tắt đèn"),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

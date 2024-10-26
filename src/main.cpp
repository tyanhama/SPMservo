#include "ServoEasing.hpp"
#include <ESP32Servo.h>
#include "WiFi.h"
#include "pin.h"
#include <Arduino.h>
#include <esp_now.h>

char buf[2];
Servo myServo;

const int minAngle = -15;
const int maxAngle = +15;
const int centerPW = 1450;
const float PWpAngle = 950/90;
int global_angle = 0;
const int minPW = 500;
const int maxPW = 2400;

float angle2PW(int angle){
    int angle2 = max(minAngle, min(angle, maxAngle));
    float PW = centerPW + PWpAngle * angle2;
    return PW;
}

void OnDataRecv(const uint8_t *mac, const uint8_t *recvData, int len) {
  memcpy(&buf[0], recvData, len);
  buf[len] = '\0';
  auto data = atoi(buf);

  if (data == 1) {  // 左ボタン
    Serial.println("BtnA");
    global_angle += 1;

  } else if (data == 2) {  // 中央ボタン
    Serial.println("BtnB");
    global_angle = 0;

  } else if (data == 4) {  // 右ボタン
    Serial.println("BtnC");
    global_angle -= 1;
  } else {
    Serial.println("Unknown");
  }
}

void setup() {
  Serial.begin(115200);

  delay(500);  // Wait for servo to reach start position.

  //   ESP Now
  WiFi.mode(WIFI_STA);  // Wi-FiをStationモードに設定

  // ESP-NOWの初期化
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //サーボ設定
  myServo.setPeriodHertz(50); // Standard 50hz servo
  myServo.attach(SERVO1_PIN, minPW, maxPW);

  esp_now_register_recv_cb(OnDataRecv);
}

long long last_time;

void loop() {
  last_time = millis();
  while (true) {
    if (millis() >= last_time + 5 * 1000) {
      last_time = millis();
      Serial.print("Mac Address is : ");
      Serial.println(WiFi.macAddress());
    }
    myServo.write(angle2PW(global_angle));
  }
}

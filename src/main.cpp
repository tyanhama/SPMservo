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

const int LED_time = 500;
unsigned long LED_R = 0; //左
unsigned long LED_W = 0; //中央
unsigned long LED_G = 0; //右

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
    LED_R = millis() + LED_time;

  } else if (data == 2) {  // 中央ボタン
    Serial.println("BtnB");
    global_angle = 0;
    LED_W = millis() + LED_time;

  } else if (data == 4) {  // 右ボタン
    Serial.println("BtnC");
    global_angle -= 1;
    LED_G = millis() + LED_time;

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

  //LED設定
    pinMode(LED_V1, OUTPUT);
    pinMode(LED_V2, OUTPUT);
    pinMode(LED_V3, OUTPUT);

  esp_now_register_recv_cb(OnDataRecv);
}

unsigned long last_time;

void loop() {
  last_time = millis();
  while (true) {
    if (millis() >= last_time + 5 * 1000) {
      last_time = millis();
      Serial.print("Mac Address is : ");
      Serial.println(WiFi.macAddress());
    }
    myServo.write(angle2PW(global_angle));
    delay(2);

    digitalWrite(LED_V1, millis() < LED_R);
    digitalWrite(LED_V2, millis() < LED_W);
    digitalWrite(LED_V3, millis() < LED_G);

    }
}


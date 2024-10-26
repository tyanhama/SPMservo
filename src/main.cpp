#include "ServoEasing.hpp"
#include "WiFi.h"
#include "pin.h"
#include <Arduino.h>
#include <esp_now.h>

char buf[2];

void OnDataRecv(const uint8_t *mac, const uint8_t *recvData, int len) {
  memcpy(&buf[0], recvData, len);
  buf[len] = '\0';
  auto data = atoi(buf);

  if (data == 1) {  // 左ボタン
    Serial.println("BtnA");
    // ここに処理を書く
  } else if (data == 2) {  // 中央ボタン
    Serial.println("BtnB");
    // ここに処理を書く
  } else if (data == 4) {  // 右ボタン
    Serial.println("BtnC");
    // ここに処理を書く
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
  }
}

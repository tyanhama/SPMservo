#include <Arduino.h>

#include "ServoEasing.hpp"
#include "pin.h"

ServoEasing Servo1;
ServoEasing Servo2;

void setup() {
    Serial.begin(115200);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_SERVO_EASING));

    /********************************************************
     * Attach servo to pin and set servo to start position.
     *******************************************************/
    Serial.println(F("Attach servo at pin " STR(SERVO1_PIN)));
    Servo1.attach(SERVO1_PIN, 45);
    Servo2.attach(SERVO2_PIN, 45);

    delay(500); // Wait for servo to reach start position.
}

void loop() {
    Serial.println(F("Move to 135 degree with 40 degree per second blocking"));
    Servo2.startEaseTo(135, 40, START_UPDATE_BY_INTERRUPT);
    Servo1.easeTo(90, 60); // Blocking call, runs on all platforms
    // Servo2.easeTo(135, 40); // Blocking call, runs on all platforms

    Serial.println(F("Move to 45 degree  with 40 degree per second blocking"));
    Servo1.easeTo(45, 60); // Blocking call, runs on all platforms
    Servo2.easeTo(45, 40); // Blocking call, runs on all platforms
    delay(1000);
}


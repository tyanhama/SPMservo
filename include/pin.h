#ifndef PIN_H
#define PIN_H

#define SERVO1_PIN 13
#define LED_V1 4
#define LED_V2 5
#define LED_V3 19

#define SPEED_IN_PIN A0           // 36/VP
#define MODE_ANALOG_INPUT_PIN A3  // 39

#define SERVO_UNDER_TEST_PIN SERVO1_PIN

#define SPEED_OR_POSITION_ANALOG_INPUT_PIN SPEED_IN_PIN
#define POSITION_ANALOG_INPUT_PIN SPEED_IN_PIN

// for ESP32 LED_BUILTIN is defined as: static const uint8_t LED_BUILTIN 2
#if !defined(LED_BUILTIN) && !defined(ESP32)
#define LED_BUILTIN PB1
#endif

#endif  // PIN_H
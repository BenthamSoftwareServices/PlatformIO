#include <Arduino.h>

#define LED1_PIN PA6 // LED D2
#define LED2_PIN PA7 // LED D3

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  // LED1 on PA6 - 1 second interval (500ms on, 500ms off)
  // LED2 on PA7 - 0.5 second interval (250ms on, 250ms off)
  // Use millis() to blink independently

  static unsigned long led1PrevMillis = 0;
  static unsigned long led2PrevMillis = 0;
  static bool led1State = false;
  static bool led2State = false;

  unsigned long currentMillis = millis();

  // LED1: toggle every 500ms → 1s full cycle
  if (currentMillis - led1PrevMillis >= 600) {
    led1PrevMillis = currentMillis;
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
  }

  // LED2: toggle every 250ms → 0.5s full cycle
  if (currentMillis - led2PrevMillis >= 250) {
    led2PrevMillis = currentMillis;
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
  }
}
#include <Arduino.h>

// Flash the orange user LED on GPIO21
const int LED_PIN = 21;

// initialize digital pin LED_PIN as an output.
void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, LOW);   // turn the LED on by making the voltage LOW
  delay(100);
  digitalWrite(LED_PIN, HIGH);  // turn the LED off (HIGH is the voltage level)
  delay(500);
}

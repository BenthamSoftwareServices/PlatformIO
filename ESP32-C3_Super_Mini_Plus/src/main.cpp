#include <Arduino.h>

void setup() {
  pinMode(8, OUTPUT); // A blue LED is connected between +3v3 and GPIO 8 with a 5K1 resistor to limit the current
}

void loop() {
  digitalWrite(8, HIGH); // Turn on the Blue LED
  delay(100);
  digitalWrite(8, LOW); // Turn off the Blue LED
  delay(1000);
}
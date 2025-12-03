/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(48, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(48, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(48, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a second
}
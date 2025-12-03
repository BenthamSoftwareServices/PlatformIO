#include <Arduino.h>

// Global counter variable (visible in debugger)
volatile unsigned long counter = 0;

int LED_BUILTIN = D10; // Pin D10

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Increment the counter each time the loop runs
  counter++;

  // Turn LED on
  digitalWrite(LED_BUILTIN, HIGH); // Turn off the LED
  delay(500);

  // Turn LED off
  digitalWrite(LED_BUILTIN, LOW); // Turn on the LED
  delay(1550);
}

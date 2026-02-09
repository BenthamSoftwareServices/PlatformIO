/*
 * Simple Blinky for STM32F030F4P6 Demo Board
 * Target LED: PA4
 */

#include <Arduino.h>

// Define the LED pin based on the Demo Board V1.1 schematic
const int boardLED = PA4; 

void setup() {
  // Initialize PA4 as an output
  pinMode(boardLED, OUTPUT);
  
  // Start Serial for debugging (requires a USB-to-UART on PA9/PA10)
  Serial.begin(115200);
  Serial.println("STM32F030F4P6 Initialised.");
}

void loop() {
  digitalWrite(boardLED, HIGH);   // Turn the LED off
  delay(100);                     // Wait for 500ms
  digitalWrite(boardLED, LOW);    // Turn the LED on
  delay(1000);                     // Wait for 500ms
  
  Serial.println("Heartbeat...");
}
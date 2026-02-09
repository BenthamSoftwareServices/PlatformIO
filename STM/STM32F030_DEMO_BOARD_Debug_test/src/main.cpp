// Simple Blinky for STM32F030F4P6 Demo Board

#include <Arduino.h>
#include <RTTStream.h>
RTTStream rtt;

// Define the LED pin based on the Demo Board V1.1 schematic
const int boardLED = PA4;
u_int32_t counter = 0;

void setup()
{
    // Initialize PA4 as an output
    pinMode(boardLED, OUTPUT);
}

void loop()
{
    digitalWrite(boardLED, HIGH); // Turn the LED off
    delay(100);                   // Wait for 500ms
    digitalWrite(boardLED, LOW);  // Turn the LED on
    delay(1000);                  // Wait for 500ms

    ++counter; // Increments first, then returns the new value

    rtt.print("counter = ");
    rtt.println(counter);
}
#include "SEGGER_RTT.h"
#include <Arduino.h>

#define LED_PIN PC13

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    SEGGER_RTT_Init(); // Initialize RTT
}

void loop() {
    digitalWrite(LED_PIN, LOW); // Turn ON LED (active low)
    delay(500);

    // Read the pin state
    int pinState = digitalRead(LED_PIN);
    SEGGER_RTT_printf(0, "LED STATE: %d\n", pinState); // Print LED state
    delay(500);
    
    digitalWrite(LED_PIN, HIGH); // Turn OFF LED (active low)
    delay(500);

    // Read the pin state again
    pinState = digitalRead(LED_PIN);
    SEGGER_RTT_printf(0, "LED STATE: %d\n", pinState); // Print LED state
    delay(500);
}
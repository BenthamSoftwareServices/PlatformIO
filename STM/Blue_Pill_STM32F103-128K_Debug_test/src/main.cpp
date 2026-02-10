/*
 * Blue Pill Onboard LED Blink
 * Target: STM32F103C8 (128KB variant)
 * LED Pin: PC13 (Active Low)
 */

#include <Arduino.h>
#include <RTTStream.h>

u_int32_t counter = 0;

// PC13 is the standard location for the onboard LED on the Blue Pill
const int ledPin = PC13; // For Blue Pill and STM32F103RET6

RTTStream rtt; // Initialise the RTT stream

void setup()
{
    // Initialise the digital pin as an output
    pinMode(ledPin, OUTPUT);
    // No baud rate needed for RTT!
    rtt.println("Blue Pill RTT Debugging Active");
}

void loop()
{
    digitalWrite(ledPin, LOW);
    rtt.print(counter);
    rtt.println(" LED ON");
    delay(100);
    digitalWrite(ledPin, HIGH);
    rtt.print(counter);
    rtt.println(" LED OFF");
    delay(100);
    counter++;
}
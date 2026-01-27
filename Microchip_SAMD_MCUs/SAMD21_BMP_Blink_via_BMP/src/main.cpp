/********************************************************************
 * Project: SAMD21_BMP_Blink_via_BMP
 * Target: SAMD21-M0-Mini (Arduino Zero Native)
 * Description: Basic Blink on Digital Pin 13
 ********************************************************************/

#include <Arduino.h>

// On the M0 Mini, D13 is often the built-in LED
const int ledPin = 13;
int counter = 5;

/**
 * @brief A blocking delay that does not use SysTick or interrupts.
 * Safe for use with debuggers (BMP/J-Link) to avoid crashes.
 * @param ms The number of milliseconds to delay.
 */

void setup()
{
    // Initialize the digital pin as an output.
    // This sets the Data Direction Register for the SAMD21 Port pin.
    pinMode(ledPin, OUTPUT);

    // Initialize Serial at 115200 for the BMP Virtual COM port (COM5)
    Serial1.begin(115200);
}

// unsigned long lastTime = 0;
// const long interval = 1000;

void loop()
{
    digitalWrite(ledPin, HIGH); // Turn off LED

    // 8 million iterations at 48MHz provides a human-visible delay
    // without using the crashing SysTick timer.
    for (uint32_t i = 0; i < 100000; i++)
    {
        __asm__("nop");
    }

    digitalWrite(ledPin, LOW); // Turn on LED

    // 8 million iterations at 48MHz provides a human-visible delay
    // without using the crashing SysTick timer.
    for (uint32_t i = 0; i < 1000000; i++)
    {
        __asm__("nop");
    }

    counter++; // Increment the counter

    // Print the heartbeat text followed by the counter value
    Serial1.print("Heartbeat... Count: ");
    Serial1.println(counter); // println adds the carriage return/line feed
}

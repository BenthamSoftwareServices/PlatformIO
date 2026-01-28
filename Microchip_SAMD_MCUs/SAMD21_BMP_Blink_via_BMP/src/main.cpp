/********************************************************************
 * Project: SAMD21_BMP_Blink_via_BMP
 * Target: SAMD21-M0-Mini (Arduino Zero Native)
 * Description: Basic Blink on Digital Pin 13
 ********************************************************************/

#include <Arduino.h>

// On the M0 Mini, D13 is often the built-in LED
const int ledPin = 13;
int counter = 5;
uint32_t led_time_off =8000000; // Set the LED off time in clock cycles
uint32_t led_time_on =1000; // Set the LED on time in mS

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
    for (uint32_t i = 0; i < led_time_off; i++)  // led_time_off could be replaced by a number e.g. 8000000 for approx 1S delay
    {
        __asm__("nop");
    }

    digitalWrite(ledPin, LOW); // Turn on LED

    for (uint32_t i = 0; i < (led_time_on); i++) // Set value in mS
    {
        for (uint32_t j = 0; j < 8000; j++) // Calibrated for ~1mS at 48MHz clock speed
        {
            __asm__ volatile("nop"); // 'volatile' prevents the compiler from optimising the loop away
        }
    }

    counter++; // Increment the counter

    // Print the heartbeat text followed by the counter value
    Serial1.print("Heartbeat... Count: ");
    Serial1.println(counter); // println adds the carriage return/line feed
}

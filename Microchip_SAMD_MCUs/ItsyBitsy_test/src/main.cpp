/*
[SUMMARY]
Migrated from blocking delay() macros to a non-blocking state machine using
the millis() function. This approach leverages the 120MHz M4 clock and
ensures the J-Link EDU mini remains synchronized via the nReset line.

[HARDWARE CONFIGURATION]
1. MCU: SAMD51G19A (120MHz, 32-bit Cortex-M4F)
2. DEBUGGER: J-Link EDU mini with physical nReset to ItsyBitsy RST pin.
3. OUTPUTS: PA22 (D13 Red LED), PA17 (Hardware Serial1 TX).
*/

#include <Arduino.h>    // Mandatory for PlatformIO to define uint32_t, pinMode, etc.
#include <RTTStream.h>  // Library for SEGGER Real Time Transfer

// Configuration constants
const uint32_t BAUD_RATE = 115200;
RTTStream rtt;
uint32_t counter = 0;

// Timing variables
uint32_t previousMillis = 0;
uint32_t currentInterval = 400;  // Do not initialise to 0 as this would cause the code to skip the
                                 // first 400ms "ON" phase and jump straight into the "OFF" phase
                                 // instantly upon startup

enum SystemState
{
    LED_ON,
    LED_OFF
};

SystemState currentState = LED_ON;

void setup()
{
    // Initialize hardware pins
    pinMode(13, OUTPUT);

    // Initialize Serial1 (Hardware TX on PA17)
    Serial1.begin(BAUD_RATE);

    // Hardware-safe wait for debugger attachment
    uint32_t startWait = millis();
    while (millis() - startWait < 1000)
    {
        __asm__ volatile("nop");
    }

    // ANSI Escape codes to clear terminal
    Serial1.print("\033[2J\033[H");
    Serial1.println("SAMD51 (M4) System Initialised...");

    digitalWrite(13, HIGH);
}

void loop()
{
    uint32_t currentMillis = millis();

    // State machine logic for non-blocking delays
    if (currentMillis - previousMillis >= currentInterval)
    {
        previousMillis = currentMillis;

        if (currentState == LED_ON)
        {
            digitalWrite(13, LOW);  // Turn LED off
            currentInterval = 500;  // Set interval for 500ms OFF
            currentState = LED_OFF;
        }
        else if (currentState == LED_OFF)
        {
            digitalWrite(13, HIGH);  // Turn LED on
            currentInterval = 400;   // Set interval for 400ms ON
            currentState = LED_ON;

            counter++;

            // Data reporting
            Serial1.print("Hardware TX on PA17 | MS: ");
            Serial1.println(millis());

            // RTT reporting
            rtt.print("M4 Counter: ");
            rtt.print(counter);
            rtt.println(" - RTT Reliable");
        }
    }
}
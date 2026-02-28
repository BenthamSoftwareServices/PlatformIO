// Black Pill Onboard LED Blink
// Target: STM32F411CE
// LED Pin: PC13 (Active Low)
// Download Segger_RTT library from https://github.com/SEGGERMicro/RTT/
// Place SEGGER_RTT library files into lib/SEGGER_RTT directory in project

#include "SEGGER_RTT.h"
#include <Arduino.h>

#define mS 500 // Define milliseconds for delay function
#define ledPin                                                                 \
    PC13 // PC13 is the standard location for the onboard Blue LED on the mini
         // board.  Using define is better than const int for pin numbers in
         // Arduino sketches.  Also helps avoid warning messages like: "No
         // symbol "PC13" in current context. (from data-evaluate-expression
         // PC13)"

u_int32_t counter =
    0; // Initialise counter variable to keep track of loop iterations

void setup()
{
    SEGGER_RTT_Init(); // Initialise the RTT system
    // Initialise the digital pin as an output
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH); // Turn LED off to set initial state
    // No baud rate needed for RTT!
    SEGGER_RTT_WriteString(0, "RTT Debugging Active\n");
}

void loop()
{
    digitalWrite(ledPin, LOW); // Turn LED on
    SEGGER_RTT_printf(0, "%d LED ON\n", counter);
    delay(mS);
    digitalWrite(ledPin, HIGH); // Turn LED off
    SEGGER_RTT_printf(0, "%d LED OFF\n", counter);
    delay(mS);
    counter++;
}
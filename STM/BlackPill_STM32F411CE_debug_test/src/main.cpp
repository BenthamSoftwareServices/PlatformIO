// Black Pill Onboard LED Blink
// Target: STM32F411CE
// LED Pin: PC13 (Active Low)

#include <Arduino.h>
#include <RTTStream.h>

#define ledPin                                                                 \
    PC13 // PC13 is the standard location for the onboard Blue LED on the mini
         // board.  Using define is better than const int for pin numbers in
         // Arduino sketches.  Also helps avoid warning messages like: "No
         // symbol "PC13" in current context. (from data-evaluate-expression
         // PC13)"

u_int32_t counter = 0;

RTTStream rtt; // Initialise the RTT stream

void setup()
{
    // Initialise the digital pin as an output
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH); // Turn LED off to set initial state
    // No baud rate needed for RTT!
    rtt.println("RTT Debugging Active");
}

void loop()
{
    digitalWrite(ledPin, LOW); // Turn LED on
    rtt.print(counter);
    rtt.println(" LED ON");
    delay(500);
    digitalWrite(ledPin, HIGH); // Turn LED off
    rtt.print(counter);
    rtt.println(" LED OFF");
    delay(500);
    counter++;
}
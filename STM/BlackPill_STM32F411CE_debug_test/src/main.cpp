//Black Pill Onboard LED Blink
//Target: STM32F411CE
//LED Pin: PC13 (Active Low)

#include <Arduino.h>
#include <RTTStream.h>

u_int32_t counter = 0;

// PB11 is the standard location for the onboard LED on the mini board
const int ledPin = PC13;

RTTStream rtt; // Initialise the RTT stream

void setup()
{
    // Initialise the digital pin as an output
    pinMode(ledPin, OUTPUT);
    // No baud rate needed for RTT!
    rtt.println("RTT Debugging Active");
}

void loop()
{
    digitalWrite(ledPin, LOW); //Turn LED on
    rtt.print(counter);
    rtt.println(" LED ON");
    delay(1000);
    digitalWrite(ledPin, HIGH); //Turn LED off
    rtt.print(counter);
    rtt.println(" LED OFF");
    delay(1000);
    counter++;
}
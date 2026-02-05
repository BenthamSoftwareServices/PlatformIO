// Blink an external LED on D10
// VITAL: Pin D8 must be pulled up to 3v3 via a 10K resistor, otherwise D8
// floats and causes debugging to fail.

#include <Arduino.h>

int ledPin = 10;
int onDelay = 500;
int offDelay = 1000;
int32_t counter = 0;

void setup() { pinMode(ledPin, OUTPUT); }

void loop()
{
    digitalWrite(ledPin, HIGH);
    delay(onDelay);
    digitalWrite(ledPin, LOW);
    delay(offDelay);

    counter++;
}

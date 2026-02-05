#include <Arduino.h>

int ledPin = 10;
int onDelay = 500;
int offDelay = 1000;

void setup() { pinMode(ledPin, OUTPUT); }

void loop()
{
    digitalWrite(ledPin, HIGH);
    delay(onDelay);
    digitalWrite(ledPin, LOW);
    delay(offDelay);
}

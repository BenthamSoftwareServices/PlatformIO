#include <Arduino.h>

int ledPin = 10;
int onDelay = 600;
int offDelay = 200;
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

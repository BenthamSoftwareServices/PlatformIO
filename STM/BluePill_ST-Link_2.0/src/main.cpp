#include <Arduino.h>

#define LED_PIN PC13
int counter = 0;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_PIN, LOW); // LED ON (active low)
    delay(100);

    digitalWrite(LED_PIN, HIGH); // LED OFF
    delay(100);
    counter++;
}
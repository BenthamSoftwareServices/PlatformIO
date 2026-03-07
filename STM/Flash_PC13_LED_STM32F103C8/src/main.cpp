#include <Arduino.h>

#define LED_PIN PC13

void setup() { pinMode(LED_PIN, OUTPUT); }

void loop()
{
    digitalWrite(LED_PIN, LOW); // ON  (active low)
    delay(500);
    digitalWrite(LED_PIN, HIGH); // OFF (active low)
    delay(500);
}
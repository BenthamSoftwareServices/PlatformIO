#include <Arduino.h>
#include "counter.h"

#define LED_Orange 21 // Builtin user LED on XIAO ESP32-S3

void setup() {
    delay(1000); // Give debugger time to attach
    pinMode(LED_Orange, OUTPUT);
}

void loop() {
    incrementCounter();

    digitalWrite(LED_Orange, HIGH); // Turn off the LED
    delay(1250);

    digitalWrite(LED_Orange, LOW); // Turn on the LED
    delay(250);
}

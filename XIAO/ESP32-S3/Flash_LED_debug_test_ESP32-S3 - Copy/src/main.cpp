#include <Arduino.h>

#define LED_Orange 21 // Builtin user LED on XIAO ESP32-S3

void setup()
{
    volatile int stop_here = 1;
    while(stop_here); // <-- Set breakpoint HERE on line 8
    
    delay(2000);
    pinMode(LED_Orange, OUTPUT);
}

void loop()
{

    digitalWrite(LED_Orange, HIGH); // Turn off the LED
    delay(1250);

    digitalWrite(LED_Orange, LOW); // Turn on the LED
    delay(250);
}

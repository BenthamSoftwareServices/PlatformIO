#include <Arduino.h>

// #define LED 21 //Built-in orange user LED on GPIO21 on XIAO ESP32-S3
#define LED LED_BUILTIN // Built-in orange user LED on GPIO21 on XIAO ESP32-S3
int count = 0;          // Initialised to zero

void setup()
{
    if (count < 100000)
    {
        // Increment the counter
        count++;
    }

    delay(100);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH); // Turn off the LED
    asm("nop");              // Use continue (F10) at this line if debugging
}

void loop()
{
    digitalWrite(LED, LOW); // Turn on the LED
    delay(250);

    digitalWrite(LED, HIGH); // Turn off the LED
    delay(250);
}

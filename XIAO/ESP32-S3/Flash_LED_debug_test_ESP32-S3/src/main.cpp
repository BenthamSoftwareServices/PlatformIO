#include <Arduino.h>

// #define LED 21 //Built-in orange user LED on GPIO21 on XIAO ESP32-S3
#define LED                                                                    \
    D1 //External LED on pin D1, which is GPIO2, so D1 or just 2 flashes D1

void setup()
{
    // The following five lines cause execution to stop if the environment (env)
    // is set to env:DEBUG otherwise they are ignored if env:RELEASE is selected
#ifdef DEBUG_SETUP
    volatile int stop_here = 1;
    while (stop_here) //Set a breakpoint at this line the spin loop in setup()
        ;
#endif

    delay(100);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH); // Turn on the LED
    asm("nop"); //Use continue (F10) at this line if debugging
}

void loop()
{
    digitalWrite(LED, LOW); // Turn off the LED
    delay(250);

    digitalWrite(LED, HIGH); // Turn on the LED
    delay(250);
}

#include <Arduino.h>

// If the Xiao becomes unresponsive press the boot button, pulse the reset
// button, release the boot button and then re-upload the code. This will put
// the Xiao into bootloader mode and allow you to upload new code to it.  It may
// be necessary to pulse the reset button again after uploading code to get the
// Xiao to start running the new code.

// XIAO ESP32-S3 Hardware Note: Onboard User LED is connected to GPIO21.

// const int ledPin = 21;
#define ledPin 21 // Define is preferred for constants in C++11 and later

void setup()
{
    // Configure GPIO21 as a digital output
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // Set GPIO21 High (LED ON)
    digitalWrite(ledPin, HIGH);
    delay(100); // 1000ms pause

    // Set GPIO21 Low (LED OFF)
    digitalWrite(ledPin, LOW);
    delay(100); // 1000ms pause
}
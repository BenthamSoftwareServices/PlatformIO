// Blink an external LED on D10 using Seeeduino Xiao ESP32-C3
// VITAL: Pin D8 must be pulled up to 3v3 via a 10K resistor, otherwise D8
// floats and causes debugging to fail.
// To start debugging first upload the code then click the debug icon, in the
// left bar, and select PIO Debug (without uploading).  The normal F5 can also
// be used but takes longer to launch.

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

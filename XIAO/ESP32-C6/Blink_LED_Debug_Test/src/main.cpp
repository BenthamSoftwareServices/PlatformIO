// Blink an external LED on D1, or the on-board yellow LED on D15
// VITAL: Pin D8 must be pulled up to 3v3 via a 10K resistor, otherwise D8
// floats and causes debugging to fail.
// To start debugging first upload the code then click the debug icon, in the
// left bar, and select PIO Debug (without uploading).  The normal F5 can also
// be used but takes longer to launch.

// ================================================================================
// HARDWARE REFERENCE: XIAO ESP32-C6 PIN SAFETY MATRIX
// ================================================================================
// ID: C6_PIN_SAFETY_001
// DATE: 05 Feb 2026
// SOURCE: SCHEMATIC V1.0 (260114)

// SAFE (Digital I/O):
// - D0 (GPIO0)
// - D1 (GPIO1) [Verified]
// - D2 (GPIO2)
// - D6 (GPIO7)
// - D7 (GPIO6)

// RESTRICTED (SDIO BUS):
// - D3, D4, D5, D10 (GPIO18-23)

// SYSTEM RESTRICTED (DO NOT USE):
// - GPIO8/9: Boot Strapping / JTAG Logic.
// - GPIO14:  RF Switch (Wi-Fi Antenna Control).
// - GPIO15:  Internal LED conflict / Strapping.
// ================================================================================

#include <Arduino.h>

// int ledPin = 1; // External LED
int ledPin = 15; // On-board LED
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

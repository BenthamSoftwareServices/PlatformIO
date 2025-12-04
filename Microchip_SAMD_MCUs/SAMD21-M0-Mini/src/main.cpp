#include <Arduino.h>

void setup() {
    SerialUSB.begin(115200);

    // Wait for SerialUSB to become active up to 2 seconds
    uint32_t startTime = millis();
    while (!SerialUSB && (millis() - startTime < 2000)) {
        // just wait, but only for 2 seconds
    }

    pinMode(13, OUTPUT);   // Built-in LED at PA17

    if (SerialUSB) {
        SerialUSB.println("SAMD21-M0-Mini: Serial loop test starting...");
    }
}

void loop() {
    static uint32_t counter = 0;

    // Toggle LED every 250 ms
    digitalWrite(13, !digitalRead(13));

    // Print counter every 1 second
    if (counter % 4 == 0) {  // 4 * 250 ms = 1 s
        if (SerialUSB) {
            SerialUSB.print("Loop counter: ");
            SerialUSB.println(counter / 4);
        }
    }

    counter++;
    delay(250);
}

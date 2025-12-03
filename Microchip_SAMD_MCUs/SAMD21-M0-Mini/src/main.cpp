#include <Arduino.h>

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB) {
    ; // Wait for USB serial to connect
  }

  SerialUSB.println("SAMD21-M0-Mini: Serial loop test starting...");

  pinMode(13, OUTPUT);   // Built-in LED at PA17
}

void loop() {
  static uint32_t counter = 0;

  // Toggle LED every 250 ms
  digitalWrite(13, !digitalRead(13));

  // Print the counter every loop (every 250 ms)
  SerialUSB.print("Loop counter: ");
  SerialUSB.println(counter);

  counter++;
  delay(2000);
}

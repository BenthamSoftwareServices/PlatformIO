#include <Arduino.h>

// Use direct PORT registers to control PA17 (D13 on your board)
constexpr uint32_t PA17_BIT = (1u << 17); // bit mask for PA17
constexpr uint8_t  PA_GROUP  = 0;         // group 0 = PAx

unsigned long counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // wait for USB serial (optional)

  // Ensure PA17 is configured as GPIO output
  // Disable peripheral multiplexer for PA17 (ensure GPIO)
  PORT->Group[PA_GROUP].PINCFG[17].reg &= ~PORT_PINCFG_PMUXEN;

  // Clear any pull-ups/downs (optional)
  PORT->Group[PA_GROUP].PINCFG[17].reg &= ~(PORT_PINCFG_INEN);

  // Set PA17 as output
  PORT->Group[PA_GROUP].DIRSET.reg = PA17_BIT;

  // Start with pin low (0V)
  PORT->Group[PA_GROUP].OUTCLR.reg = PA17_BIT;
}

void loop() {
  counter++;
  Serial.print("hello world #");
  Serial.println(counter);

  // Toggle PA17
  PORT->Group[PA_GROUP].OUTTGL.reg = PA17_BIT;

  delay(500); // 500 ms on, 500 ms off (meter-friendly)
}

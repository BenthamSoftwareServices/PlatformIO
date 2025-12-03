/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

void setup() {
			  // initialize digital pin LED_BUILTIN as an output.
			  pinMode(48, OUTPUT);
			}

			void loop() {
			  digitalWrite(48, HIGH);  // turn the LED on (HIGH is the voltage level)
			  delay(5000);                      // wait for a second
			  digitalWrite(48, LOW);   // turn the LED off by making the voltage LOW
			  delay(5000);                      // wait for a second
			}

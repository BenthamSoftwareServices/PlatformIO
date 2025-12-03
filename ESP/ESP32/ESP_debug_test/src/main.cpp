/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework i.e. using board = esp32dev
// Comment out if using board = esp32doit-devkit-v1 as LED_BUILTIN is defined therein
#define LED_BUILTIN 2

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200); //same speed as defined for the serial monitor in platformio.ini
  Serial.println("Start");
}

int delayTime = 100;

void blink_led()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED off (HIGH is the voltage level)
  Serial.println("The Blue LED is off");
  delay(delayTime); // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED on by making the voltage LOW
  Serial.println("The Blue LED is on");
  Serial.println(ESP.getFlashChipSize(),HEX);
  Serial.println(ESP.getFreeSketchSpace(),HEX);
  delay(delayTime); // wait for a second
}

void loop()
{
blink_led();
}


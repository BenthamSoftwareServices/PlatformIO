/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
#define LED_BUILTIN 2

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200); //same speed as defined for the serial monitor in platformio.ini
  Serial.println("Start");
}

int delayTime = 200;

void blink_led()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  //Serial.println("The Blue LED is on");
  delay(delayTime); // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  //Serial.println("The Blue LED is off");
  //Serial.println(ESP.getFlashChipSize());
  //Serial.println(ESP.getFreeSketchSpace());
  delay(delayTime); // wait for a second
}

void loop()
{
blink_led();
}


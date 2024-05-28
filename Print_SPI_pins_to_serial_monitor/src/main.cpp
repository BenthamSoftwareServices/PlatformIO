// This program prints the GPIO pin numbers for the four main SPI pins on the ESP32 as specified in the board DOIT ESP32 Dev Kit V1
// The pin data will be printed to the serial port deined in platformio.ini
// All the functions of the ESP32 and the pins assigned can be viewed by right clicking the "SPI.h" include and selecting Go to definition
// Once the file SPI.h is open right click the include "pins_arduino.h" to view

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define LED 2 //GPIO Pin 2 defined as constant named LED

void setup(void)
{
  Serial.begin(115200);

  // Set pin mode for LED pin
  pinMode(LED, OUTPUT);
}

void loop(void)
{
  Serial.print("MOSI Output is on: ");
  Serial.println(MOSI);

  Serial.print("MISO Input is on: ");
  Serial.println(MISO);

  Serial.print("SCK is on: ");
  Serial.println(SCK);

  Serial.print("SS/CS Slave/Chip Select is on: ");
  Serial.println(SS);

  Serial.println("=====================");

// Blink built in LED to show loop is active.
  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}

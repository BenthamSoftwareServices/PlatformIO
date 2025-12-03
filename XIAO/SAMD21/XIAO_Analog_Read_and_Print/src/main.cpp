#include <Arduino.h>

/*
  Seeeduino XIAO Analog Input Demo
  xiao-analog-in-test.ino
  Displays operation of XIAO A/D converter
  Results displayed on Serial Monitor

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Analog Input Pin
#define ANALOG_IN_PIN A2

// Integer to represent input value
int input_val;

void setup() 
{
  // Set A/D converter resolution to 12-bits
  analogReadResolution(12); 
  
  // Setup Serial Port
  Serial.begin(9600);
}

void loop() 
{
  // Read the input value
  input_val = analogRead(ANALOG_IN_PIN);  
  input_val = map(input_val, 3, 4091, 0, 100);
  
  // Print value to Serial Monitor
  Serial.println(input_val);
  
  // Slight delay before repeating
  delay(1000); 
  
}
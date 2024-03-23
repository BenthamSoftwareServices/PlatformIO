//SCULLCOM HOBBY ELECTRONICS
//ELECTRONIC DC LOAD PROJECT
//Software Version 27
//13th July 2017

#include <Arduino.h>

#include <SPI.h>                              //include SPI library (Serial Peripheral Interface)
#include <Wire.h>                             //include I2C library
#include <LiquidCrystal_I2C.h>                // F Malpartida's NewLiquidCrystal library  https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/NewliquidCrystal_1.3.4.zip
#include <math.h>                             //
#include <Adafruit_MCP4725.h>                 //Adafruit DAC library  https://github.com/adafruit/Adafruit_MCP4725
#include <MCP342x.h>                          //Steve Marple library avaiable from    https://github.com/stevemarple/MCP342x
#include <MCP79410_Timer.h>                   //Scullcom Hobby Electronics library  http://www.scullcom.com/MCP79410Timer-master.zip
#include <Keypad.h>                           //http://playground.arduino.cc/Code/Keypad

#define LED_BUILTIN 2 //also known as pin D9

LiquidCrystal_I2C lcd(0x3F);  // Set the LCD I2C address

int delayTime = 500;

void setup() {
  // put your setup code here, to run once:
   // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(20,4);
}

void blink_led()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(delayTime); // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(delayTime); // wait for a second
}

void loop() {
  // put your main code here, to run repeatedly:
  blink_led();
}
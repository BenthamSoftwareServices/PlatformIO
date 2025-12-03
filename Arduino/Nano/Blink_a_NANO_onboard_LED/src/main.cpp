#include <Arduino.h>

/*
* Blink_Randomly
*
* Modified from the basic Arduino example.  Turns an LED on for a random time,
* then off for a (most likely) different random time.  We use digital pin 4 
* or PD4 (Port D4) which is pin 6 on the 28-pin PDIP package.
*
* Original at - http://www.arduino.cc/en/Tutorial/Blink
*/

int ledPin = 13;                  // LED connected to digital pin 4 or PD4 (Port D4) which is pin 6 on the 28-pin PDIP package
long randOn = 0;                  // Initialize a variable for the ON time
long randOff = 0;                 // Initialize a variable for the OFF time


void setup()                      // run once, when the sketch starts
{
 randomSeed (analogRead (0));    // randomize
 pinMode(ledPin, OUTPUT);        // sets the digital pin as output
}

void loop()                       // run over and over again
{
 randOn = random (100, 1500);    // generate ON time between 0.1 and 1.5 seconds
 randOff = random (200, 900);    // generate OFF time between 0.2 and 0.9 seconds
   digitalWrite(ledPin, HIGH);   // sets the LED on
   delay(randOn);                // waits for a random time while ON
   digitalWrite(ledPin, LOW);    // sets the LED off
   delay(randOff);               // waits for a random time while OFF
}
#include <Arduino.h>

/*  This example uses the millis() function to read the mS count each pass through main loop and check if more than
 *  a predefined interval has elapsed, if it has the state of a LED is inverted; three LEDs are connected to pins 11,12 & 13
 *  (millis() is not precisely accurate as each count is 1.024mS, not 1.000mS, which is corrected by software when drift approaches 1mS)
*/

#define INTERVAL_1 356  // {mS]
#define INTERVAL_2 1117  // {mS]
#define INTERVAL_3 2053  // {mS]

byte led_1; //led_1 status 0=off, 1=on
byte led_2; //led_2 status 0=off, 1=on
byte led_3; //led_2 status 0=off, 1=on
unsigned long time_for_action_1;
unsigned long time_for_action_2;
unsigned long time_for_action_3;

void setup() {
  pinMode(13, OUTPUT);   //set pin 13 to be an output
  pinMode(12, OUTPUT);   //set pin 12 to be an output
  pinMode(11, OUTPUT);   //set pin 11 to be an output
}

void loop() {
  // put your main code here, to run repeatedly:

    if (millis() > time_for_action_1) {
    time_for_action_1 = millis() + (unsigned long)INTERVAL_1;
    led_1 = !led_1; //invert the value of led_1
    }

    if (millis() > time_for_action_2) {
    time_for_action_2 = millis() + (unsigned long)INTERVAL_2;
    led_2 = !led_2; //invert the value of led_2
    }

    if (millis() > time_for_action_3) {
    time_for_action_3 = millis() + (unsigned long)INTERVAL_3;
    led_3 = !led_3; //invert the value of led_3
    }

  digitalWrite(13,led_1); //write the value of led_1 to pin 13
  digitalWrite(12,led_2); //write the value of led_2 to pin 12
  digitalWrite(11,led_3); //write the value of led_3 to pin 11
}
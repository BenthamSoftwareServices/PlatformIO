/*Conditional Breakpoints e.g. count=5 will set the variable count to the value 5 when execution gets to it,
  however count==5 will do nothing, until count reaches the value 5 after being incremented in other parts of the code,
  at which point it will cause the breakpoint to be triggered and execution will halt. To stop at a conditional breakpoint
  when count is equal to, or greater than, 5 then use count>--5.*/

#include <Arduino.h>
#include "avr8-stub.h"
// #include "app_api.h" // only needed with Flash breakpoints

int count = 0;
int count1 = 0;

void setup()
{
  debug_init();
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  // Serial.begin(9600);
  // Serial.println(count);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
  delay(100);
  digitalWrite(LED_BUILTIN, LOW); // Turn off LED
  delay(100);
  count++;
  count1++;
  delay(100);
}

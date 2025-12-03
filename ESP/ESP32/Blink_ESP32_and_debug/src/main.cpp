#include <Arduino.h> //part of PlatformIO Arduino framework
#include "Arduino_GFX_Library.h" //in lib folder
#include "RunningAverage.h" //in lib folder

// put function declarations here:
int count = 0;
static unsigned long counter = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  Serial.begin(115200); // send and receive at 9600 baud
}

void loop() {
  // put your main code here, to run repeatedly:

// turn the LED off (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(100);

  // turn the LED on by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

  // wait for a second
  delay(100);

  count++;
  counter++;

  printf("The value of count is: %d \n", count);

}

// put function definitions here:

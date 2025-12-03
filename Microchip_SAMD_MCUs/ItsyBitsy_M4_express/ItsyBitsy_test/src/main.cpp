#include <Arduino.h> // Include Arduino core library
#include <RTTStream.h> // Include RTTStream library

RTTStream rtt;  // Create RTTStream object

int counter = 0; // Initialize counter variable

void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as output (usually connected to onboard LED) PA22 on MCU
}

void loop() {
  digitalWrite(13, HIGH);  // Red LED on
  delay(100);
  digitalWrite(13, LOW);   // Red LED off
  delay(100);
  counter++;

  // Use Real Time Transfer to stream data to RTT Viewer app on host PC
  rtt.print("Counter: ");  // Use RTTStream to print counter value
  rtt.print(counter); // Print the current counter value
  rtt.println(" - Hello world!"); // Print a message
}

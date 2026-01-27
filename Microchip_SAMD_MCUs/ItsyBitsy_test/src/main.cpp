#include <Arduino.h> // Include Arduino core library
#include <RTTStream.h> // Include RTTStream library, an alternative to Serial1 for real-time data transfer

const long BAUD_RATE = 115200;

RTTStream rtt;  // Create RTTStream object

int counter = 0; // Initialize counter variable

void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as output (usually connected to onboard LED) PA22 on MCU
  delay(2000);  // Give debugger time to fully attach
  Serial1.begin(BAUD_RATE); // Initialize Serial1 at BAUD_RATE
  Serial1.print("\033[2J\033[H");  // Clear terminal screen and move cursor to home position
  #ifdef DEBUG
    Serial1.flush();  // Only flush when debugging, to ensure all data is sent
  #endif
  
}

void loop() {
  digitalWrite(13, HIGH);  // Red LED on
  delay(500);
  digitalWrite(13, LOW);   // Red LED off
  delay(500);
  counter++;

Serial1.print("Hardware TX on PA17 ");
#ifdef DEBUG
    Serial1.flush();  // Only flush when debugging
  #endif
  Serial1.println(millis());
#ifdef DEBUG
    Serial1.flush();  // Only flush when debugging
  #endif

  //Use Real Time Transfer to stream data to RTT Viewer app on host PC
  rtt.print("Counter: ");  // Use RTTStream to print counter value
  rtt.print(counter); // Print the current counter value
  rtt.println(" - Hello world!"); // Print a message
}

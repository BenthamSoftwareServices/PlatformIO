/*
 * blink.cpp
 * Example project for the Arduino debugger.
 * Blinks the LED on Arduino Mega board.
 * For instructions on use please see doc\avr_debug.pdf
 *
 *  Created on: 19. 1. 2017
 *  Author: Jan Dolinay
 */
#include "Arduino.h"
#include "avr8-stub.h"

int count = 0;
int count1 = 0;

void setup(void)
{
	debug_init(); // initialize the debugger
	delay(500);
	pinMode(13, OUTPUT); // Onboard LED on GPIO13
	Serial1.begin(9600); // Serial1 is the second USART on a 2560 i.e. USART1, the first is USART0
	Serial1.println(count); // Print value of variable count to USART1
}

void loop(void)
{
	digitalWrite(13, HIGH); // Turn on LED
	delay(200);
	digitalWrite(13, LOW); // Turn off LED
	delay(1000);
	count++;
	count1++;
}
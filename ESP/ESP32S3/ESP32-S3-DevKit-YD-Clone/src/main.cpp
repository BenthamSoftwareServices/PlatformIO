/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#define FASTLED_INTERNAL // This is vital to add before FastLED include or the compiler outputs a harmless but annoying message about unused SPI pins
#include <FastLED.h>

#define LED_PIN 48
#define NUM_LEDS 1

#define ON 10 // dim brightness for LEDs, max is 255
#define OFF 0 // OFF brightness for LEDs

int delay_time = 1000;

CRGB leds[NUM_LEDS];

void setup()
{

	// FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
	// Use CRGB::Blue; //Blue using auto-complete, just start typing a colour, or numbers from 0-255
	// Can also use digitalWrite (RGB_BUILTIN, HIGH) for a white colour, or LOW for OFF
	leds[0] = CRGB(ON, OFF, OFF); // Red
	FastLED.show();
	delay(delay_time);

	leds[0] = CRGB(OFF, ON, OFF); // Green
	FastLED.show();
	delay(delay_time);

	leds[0] = CRGB(OFF, OFF, ON); // Blue
	// leds[0] = CRGB::Blue; //Blue using auto-complete, just start typing a colour
	FastLED.show();
	delay(delay_time);
}
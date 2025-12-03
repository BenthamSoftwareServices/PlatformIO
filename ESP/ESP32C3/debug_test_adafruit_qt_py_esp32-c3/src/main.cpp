/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

#define FASTLED_INTERNAL //This is vital to add before FastLED include or the compiler outputs a harmless but annoying message about unused SPI pins
			#include <FastLED.h>

			#define LED_PIN     48
			#define NUM_LEDS    1

      int delay_time = 100;

			CRGB leds[NUM_LEDS];

			void setup() {
			  
			//FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
			  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
			  
			}

			void loop() {
			  
			  leds[0] = CRGB(255, 0, 0); //Red
			  FastLED.show();
			  delay(delay_time);

			  leds[0] = CRGB(0, 255, 0); //Green
			  FastLED.show();
			  delay(delay_time);

			  leds[0] = CRGB::Blue; //Blue using auto-complete, just start typing a colour
			  FastLED.show();
			  delay(delay_time);
			}
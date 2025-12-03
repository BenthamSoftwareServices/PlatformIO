#include <Arduino.h>

/*
 * This sketch uses two RTOS tasks to print to serial and flash the on-board NeoPixel
 * Adafruit_NeoPixel Class Reference: https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
 * NOTE: On ESP32xx MCUs delay() calls vTaskDelay() and is therefore interchangeable,
 * see: https://github.com/espressif/arduino-esp32/blob/396def3f837ced99a20ebbff2516558879653f03/cores/esp32/esp32-hal-misc.c#L202-L204
*/
#include <Adafruit_NeoPixel.h> // A library to control one, or more, NeoPixel LEDs

int PIN = 48;       // The NeoPixel RGB LED is connected to pin 48 on the ESP32_S3_DevKitC_1 module, and is a WS2812B device, see: https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf
int DELAY_VAL = 500; // Common delay value between colour changes
int count = 0;      // A test value


Adafruit_NeoPixel pixels(
	1,                       // Number of NeoPixel LEDs
	PIN,                     // GPIO pin connected to NeoPixel
	NEO_GRB +                // Define type of NeoPixel, in this case RGB means RED, GREEN & BLUE, some are GRB.  For pixels.Color NEO_RGB = (G,R,B) and NEO_GRB = (R,G,B) strangely! Probably only impacts strings of NeoPixels.
	NEO_KHZ800               // Interface speed for NeoPixel device, usually 400 or 800
);

void setup() {

	Serial.begin(115200);
	pixels.begin();                                             // INITIALIZE NeoPixel object (REQUIRED)
}
void loop() {
	count++;  // This variable starts at 0 and increments every 1000mS
	vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 1000mS

    Serial.println("flashing");

		pixels.clear();  // Set all pixel colours to 'off'
		pixels.show();   // Send the updated pixel colours to the hardware.
		vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 1000mS

		// The first NeoPixel in a strand is #0, second is 1 et cetera
		// pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255

		pixels.setPixelColor(0, pixels.Color(10, 0, 0)); // Red using NEO_GRB
		pixels.show();   // Send the updated pixel colours to the hardware.
		delay(DELAY_VAL); // Pause before next pass through loop

		pixels.setPixelColor(0, pixels.Color(0, 10, 0)); // Green using NEO_GRB
		pixels.show();   // Send the updated pixel colours to the hardware.
		delay(DELAY_VAL); // Pause before next pass through loop

		pixels.setPixelColor(0, pixels.Color(0, 0, 10)); // Blue using NEO_GRB
		pixels.show();   // Send the updated pixel colours to the hardware.
		delay(DELAY_VAL); // Pause before next pass through loop

    //Serial.print("printing = ");
		//Serial.print(count);
		//Serial.println();
		vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 15000mS

}
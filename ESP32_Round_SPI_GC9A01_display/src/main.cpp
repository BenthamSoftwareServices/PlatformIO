#include <Arduino.h>

/*******************************************************************************
 * Start of Arduino_GFX setting
 *
 * Arduino_GFX try to find the settings depends on selected board in Arduino IDE
 * Or you can define the display dev kit not in the board list
 * Defalult pin list for non display dev kit:
 * 
 * ESP32 various dev board     : CS:  5, DC: 16, RST: 7, BL: 22
 * 
 ******************************************************************************/
#include <Arduino_GFX_Library.h>

#define GFX_BL 22 // Display backlight pin, LOW = display off and HIGH = display on, see lines 45-48

/* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
//Arduino_DataBus *bus = create_default_Arduino_DataBus();
Arduino_DataBus *bus = new Arduino_ESP32SPI(16 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, GFX_NOT_DEFINED /* MISO */, VSPI /* spi_num */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
//Arduino_GFX *gfx = new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);

#endif /* !defined(DISPLAY_DEV_KIT) */
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

/* more fonts at: https://github.com/moononournation/ArduinoFreeFontFile.git */
// Note: put header files in the project include folder and use double quotes to enclose file names.
// Note: compilation may be required before header files are recognised i.e. no red squiggles.
#include "FreeMono8pt7b.h"
#include "FreeSansBold10pt7b.h"
#include "FreeSerifBoldItalic12pt7b.h"

void setup(void)
{
  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT); // GPIO 22 set as output
  digitalWrite(GFX_BL, HIGH); // Enable display backlight
#endif

  gfx->setCursor(10, 10);
  gfx->setFont(&FreeMono8pt7b);
  gfx->setTextColor(RED);
  gfx->println("Hello World!");

  delay(2000); // 2 seconds
}

void loop()
{
  gfx->setCursor(random(gfx->width()), random(gfx->height()));
  gfx->setTextColor(random(0xffff));
  uint8_t textSize = random(3);
  switch (textSize)
  {
  case 1:
    gfx->setFont(&FreeMono8pt7b);
    break;
  case 2:
    gfx->setFont(&FreeSansBold10pt7b);
    break;
  default:
    gfx->setFont(&FreeSerifBoldItalic12pt7b);
    break;
  }

  gfx->println("Hello World!");

  delay(1000); // 1 second
}
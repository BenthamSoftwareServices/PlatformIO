#include <Arduino.h>

#include <Wire.h>                           // For I2C communications
#include <hd44780.h>                        // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header

/*-----( Declare Constants )-----*/
// LCD geometry
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

/*-----( Declare objects )-----*/
//hd44780_I2Cexp lcd;  // declare lcd object: auto locate & auto config expander chip
 hd44780_I2Cexp lcd(0x27);

 /*-----( Declare Variables )-----*/
 int status;

 void setup()
 {
   status = lcd.begin(LCD_COLS, LCD_ROWS);
   if (status) // non zero status means it was unsuccesful
   {
     // hd44780 has a fatalError() routine that blinks an led if possible
     // begin() failed so blink error code using the onboard LED if possible
     hd44780::fatalError(status); // does not return
   }

   // Print a message to the LCD.
   lcd.clear();
   delay(500);
   lcd.setCursor(0, 0);
   lcd.print("Time elapsed");
   delay(500);
     
 } /*--(end setup )---*/

void loop() {
  // Here cursor is placed on first position (col: 0) of the second line (row: 1)
  lcd.setCursor(0, 1);
  // We write the number of seconds elapsed
  lcd.print(millis() / 1000);
  // Now we print the word Seconds with an initial space
  lcd.print(" Seconds");
  delay(1000);
}
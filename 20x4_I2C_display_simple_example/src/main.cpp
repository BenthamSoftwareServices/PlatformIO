#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


/*#define I2C_ADDR       0x3F // I2C address of display
#define BACKLIGHT_PIN  3
#define En_pin         2
#define Rw_pin         1
#define Rs_pin         0
#define D4_pin         4
#define D5_pin         5
#define D6_pin         6
#define D7_pin         7
*/

// initialize the library with the display I2C address and the numbers of the interface pins
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // alternative method
//LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);

void setup()  
{
  lcd.begin(20,4); 
  lcd.setCursor(3,0);
  lcd.print("Hello Steven999!");
  lcd.setCursor(8,1);
  lcd.print("****");
  lcd.setCursor(0,2);
  lcd.print("This is a demo text");
  lcd.setCursor(8,3);
  lcd.print("****");
}

void loop() 
{ 
}

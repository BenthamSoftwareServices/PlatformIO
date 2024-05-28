#include <Arduino.h>

 /*This sketch initialises a 20 x 4 LCD, writes some text and uses and ISR to detect when a rotary switch
 * changes position, reads the direction of travel pin (DT) and increments, or decrements, a counter. The
 * main loop examines the counter and if changed writes the new value to the LCD and serial monitor for 
 * debugging.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //I2C version of LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/

#define I2C_ADDR       0x3F // I2C address of PCF8574 8-bit I/O expander for I2C-bus driving LCD display
#define BACKLIGHT_PIN  3    // P3 (Pin 7) of PCF8574 8-bit I/O expander for I2C-bus
#define En_pin         2    // P2 (Pin 6) of PCF8574 8-bit I/O expander for I2C-bus
#define Rw_pin         1    // P1 (Pin 5) of PCF8574 8-bit I/O expander for I2C-bus
#define Rs_pin         0    // P0 (Pin 4) of PCF8574 8-bit I/O expander for I2C-bus
#define D4_pin         4    // P4 (Pin 9) of PCF8574 8-bit I/O expander for I2C-bus
#define D5_pin         5    // P5 (Pin10) of PCF8574 8-bit I/O expander for I2C-bus
#define D6_pin         6    // P6 (Pin11) of PCF8574 8-bit I/O expander for I2C-bus
#define D7_pin         7    // P7 (Pin12) of PCF8574 8-bit I/O expander for I2C-bus

//initialize the library with the display I2C address and the numbers of the interface pins
//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // alternative method
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);
// the parameters passed to the lcd function of the LiquidCrystal_I2C library establish mapping between LCD pin function and the
// port number Pn of the PCF8574 8-bit I/O expander

//Variables to store condition of rotary encoder pins
// Used for generating interrupts using CLK signal
const int PinCLK = 2; //INT0

// Used for reading DT (Direction od Travel) signal
const int PinDT = 4; //Digital pin 4 or D4

// Used for the push button switch
const int PinSW = 8; //Digital pin 8 or D8

// Keep track of last rotary value
int lastCount = 50;

// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 50;  //volatile means store on RAM not a CPU register

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void isr ()
    {
     static unsigned long lastInterruptTime = 0;
     unsigned long interruptTime = millis();

//  If interrupts come faster than 50ms, assume it's a bounce and ignore
    if (interruptTime - lastInterruptTime > 50) {
    if (digitalRead(PinDT) == LOW)
    {
      virtualPosition-- ; // Could be -5 or -10
    }
    else {
      virtualPosition++ ; // Could be +5 or +10
    }

//  Restrict value from 0 to +100
    virtualPosition = min(100, max(0, virtualPosition));

    }
//  Keep track of when we were here last (no more than every 5ms)
    lastInterruptTime = interruptTime;
    }

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {
//  Just whilst we debug, view output on serial monitor
    Serial.begin(115200); //remember to set serial monitor to matching baud rate or it displays garbage characters!

//  Rotary pulses are INPUTs
    pinMode(PinCLK, INPUT);
    pinMode(PinDT, INPUT);

//  Switch is floating so use the in-built PULLUP so we don't need a resistor
    pinMode(PinSW, INPUT_PULLUP);

//  Attach the routine to service the interrupts
    attachInterrupt(digitalPinToInterrupt(PinCLK), isr, LOW);

//  Ready to go!
    Serial.println("Start");

  lcd.begin(20,4); 
  lcd.setCursor(0,0);
  lcd.print("Vintage Radio PSU");
  lcd.setCursor(8,1);
  lcd.print("****");
  lcd.setCursor(0,2);
  lcd.print("Volts AC to radio");
  lcd.setCursor(0,3);
  lcd.print("Cycles to stop");
  lcd.setCursor(15,3);
  lcd.print(virtualPosition);
}
// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop()
  {
//  Is someone pressing the rotary switch?
    if ((!digitalRead(PinSW))) {
    virtualPosition = 50;
    while (!digitalRead(PinSW))
    delay(10);
    Serial.println("Reset");
  }

//  If the current rotary switch position has changed then update everything
    if (virtualPosition != lastCount) {

//  Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
    Serial.println(virtualPosition);

      lcd.setCursor(15,3);
      lcd.print(virtualPosition);

//  Keep track of this new value
    lastCount = virtualPosition ;
  }
  delay(100);
//blink cycles value
lcd.setCursor(15,3);
      lcd.print(virtualPosition);

      delay(1000);

      lcd.setCursor(15,3);
      lcd.print("xx");

      delay(1000);
  
  }
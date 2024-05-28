
//For display wiring see: https://i0.wp.com/dronebotworkshop.com/wp-content/uploads/2022/06/GC9A01-ESP32-Hookup.jpg?w=768&ssl=1

#include <Arduino.h> //part of PlatformIO Arduino framework
#include "Arduino_GFX_Library.h" //in lib folder
#include "RunningAverage.h" //in lib folder

// put function declarations here:
//#define PIN_BLK 34  //spcify an unused GPIO pin, or comment out this definition, if the display backlight is not used.
#define PIN_CS  22
#define PIN_DC  16
#define PIN_RES 4
#define PIN_SDA 23
#define PIN_SCL 18

#define GFX_BL PIN_BLK

Arduino_DataBus *bus = new Arduino_HWSPI(PIN_DC, PIN_CS);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, PIN_RES, 0 /* rotation */, true /* IPS */, 240 /* width */, 240 /* height */);
//Arduino_GFX *gfx = new Arduino_Canvas(240 /* width */, 240 /* height */, output_display);

// Create a canvas
//Arduino_Canvas *canvas = new Arduino_Canvas(240, 240, gfx);

RunningAverage myRA(20);
uint16_t r,r0;
//uint16_t d=0;
//uint16_t counter=0;
uint16_t v_inVal;
uint16_t i;
float p,p_avg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
while (!Serial)
Serial.print("Sketch: "); Serial.println(__FILE__);
Serial.print("Uploaded: "); Serial.println(__DATE__);
gfx->begin(80000000);
//canvas->begin();
r = gfx->width();
r0=r/2;
analogSetAttenuation(ADC_6db);
myRA.clear();
}

void drawE5(uint16_t v_i){
/*
canvas->fillScreen(gfx->color565(37,234,61));
canvas->fillTriangle(r0,r0+10, r0-v_i,r,r0+v_i,r,gfx->color565(28,152,53));
canvas->fillTriangle(0,r0, r0,r0-8,r0,r0+8,gfx->color565(20,140,40));
canvas->fillTriangle(r,r0, r0,r0-8,r0,r0+8,gfx->color565(20,140,40));
canvas->fillCircle(r0+2,r0+2, 52, gfx->color565(40,40,40));
canvas->fillCircle(r0-3,r0-2, 52, gfx->color565(150,162,160));
canvas->fillCircle(r0,r0, 52, gfx->color565(71,76,69));
delay(1000);
delay(1000);
delay(1000);
canvas->flush();
*/

gfx->fillScreen(gfx->color565(37,234,61));
gfx->fillTriangle(r0,r0+10, r0-v_i,r,r0+v_i,r,gfx->color565(28,152,53));
gfx->fillTriangle(0,r0, r0,r0-8,r0,r0+8,gfx->color565(20,140,40));
gfx->fillTriangle(r,r0, r0,r0-8,r0,r0+8,gfx->color565(20,140,40));
gfx->fillCircle(r0+2,r0+2, 52, gfx->color565(40,40,40));
gfx->fillCircle(r0-3,r0-2, 52, gfx->color565(150,162,160));
gfx->fillCircle(r0,r0, 52, gfx->color565(71,76,69));
gfx->flush();

}

void loop() {
  // put your main code here, to run repeatedly:
p=analogRead(34);
myRA.addValue(p);
p_avg=myRA.getAverage();
i=map(p_avg,50,1000,120,20);
// i=map(p_avg,50,1200,20,200);
if (i<0) i=0;
drawE5(i);
//delay(1000);
}

// put function definitions here:
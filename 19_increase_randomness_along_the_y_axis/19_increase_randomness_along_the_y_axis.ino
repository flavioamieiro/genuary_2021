#include <GxEPD2_BW.h>
#include <FastLED.h>
#define MIN_LEN 200
#define NOISE_SCALE 0.035

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void setup() {
  initDisplay();
  for (int y=0; y<display.height(); y++) {
    //display.drawLine(0, y, random(0, y), y, GxEPD_BLACK);
    display.drawLine(0, y, MIN_LEN + inoise8((float)y*((float)y*NOISE_SCALE)), y, GxEPD_BLACK);
  }
  display.display();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.clearScreen();
  display.fillScreen(GxEPD_WHITE);
}



void loop() {
}

#include <GxEPD2_BW.h>
#include <FastLED.h>

#define NUM_LINES 500
#define LEN 400

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void setup() {
  initDisplay();
  draw();
  display.display();
}

void draw() {
  int rand_offset = random(0, 1000);
  int yoffset = ((display.height() - NUM_LINES)/2);
  for (int i=0; i<NUM_LINES; i++) {
    int startx = (display.width() - LEN)/2;
    int starty = yoffset + i;
    int endx = startx + LEN;
    int endy = starty + map(inoise8(rand_offset+(float)i), 0, 255, -150, 150);
    display.drawLine(startx, starty, endx, endy, GxEPD_BLACK);
  }
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
}


void loop() {}

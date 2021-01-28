#include <GxEPD2_BW.h>
#define ANG_STEP PI/180

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));


void setup() {
  initDisplay();
  for (int i=0; i<display.width(); i+=50) {
    drawSine(i);
  }
  display.display();
}

void drawSine(int offs) {
  for (int x=0; x<display.width(); x++) {
    int y = display.height()/2 + 100 * sin((offs+x)*ANG_STEP);
    display.drawPixel(x, y, GxEPD_BLACK);
  }
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}


void loop() {
}

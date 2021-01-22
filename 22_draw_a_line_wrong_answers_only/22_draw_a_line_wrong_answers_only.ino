#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
  display.clearScreen();
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  
  for (int x=0; x<display.width(); x++) {
    int r = random(0, (display.height()/2));
    int yoffs = random(r*-1, r);
    display.drawPixel(x, (display.height()/2)+yoffs, GxEPD_BLACK);
  } 
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

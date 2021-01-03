#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
}

void fullRefresh() {
  display.fillScreen(GxEPD_WHITE);
  display.refresh(false);
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  for (int x=0; x<40; x++){
    for (int y=0; y<40; y++) {
      uint16_t color = GxEPD_WHITE;
      if (random(0, 10) >= 5) {
        color = GxEPD_BLACK;  
      }
      display.fillRect(x*20, y*12, 20, 12, color);
    }
  }
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

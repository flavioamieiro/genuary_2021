#include <GxEPD2_BW.h>
#define X_STEP 10
#define Y_STEP 10

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
  display.clearScreen();
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  for (int r=0; r<=4; r+=1) {
    display.setRotation(r);
    for (int i=0; i<=loop_count; i++) {
      int start_x = 0;
      int end_x = X_STEP * i;
      int start_y = Y_STEP * i;
      int end_y = display.height();
      display.drawLine(start_x, end_x, start_y, end_y, GxEPD_BLACK);
    }
  }
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

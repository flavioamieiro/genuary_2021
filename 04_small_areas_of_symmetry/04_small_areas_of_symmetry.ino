#include <GxEPD2_BW.h>

#define PADDING 4

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

void recursiveRect(int x, int y, int w, int h) {
  display.drawRect(x, y, w, h, GxEPD_BLACK);
  if (w > 10 && h > 10) {
    int new_w = (w / 2) - (2 * PADDING);
    int new_h = (h / 2) - (2 * PADDING);
    int left_x = (x + PADDING);
    int right_x = ((x + w) - PADDING - new_w);
    int top_y = (y + PADDING);
    int bottom_y = ((y + h) - PADDING - new_h); // (y + new_h + (3 * PADDING));
    recursiveRect(left_x, top_y, new_w, new_h);
    recursiveRect(right_x, top_y, new_w, new_h);
    recursiveRect(left_x, bottom_y, new_w, new_h);
    recursiveRect(right_x, bottom_y, new_w, new_h);
  }
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
//  recursiveRect(10, 10, display.width() - 20, display.height() - 20);
  for (int i=5; i<15; i++) {
    recursiveRect(i*PADDING + 180, i*PADDING, 400, 400);
  }
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

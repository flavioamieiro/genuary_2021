#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
}

void fullRefresh() {
  display.clearScreen();
}

void sierpinsky(int x0, int y0, int x1, int y1, int x2, int y2) {
  int left_middle_x = x0+(x1-x0)/2;
  int left_middle_y = y1+(y0-y1)/2;
  int bottom_middle_x = x0+(x2-x0)/2;
  int right_middle_x = x1+(x2-x1)/2;
  int right_middle_y = y1+(y2-y1)/2;
  display.drawTriangle(x0, y0, left_middle_x, left_middle_y, bottom_middle_x, y2, GxEPD_BLACK);
  display.drawTriangle(left_middle_x, left_middle_y, x1, y1, right_middle_x, right_middle_y, GxEPD_BLACK);
  display.drawTriangle(bottom_middle_x, y2, right_middle_x, right_middle_y, x2, y2, GxEPD_BLACK);
  if ((bottom_middle_x - x0) > 3) {
    sierpinsky(x0, y0, left_middle_x, left_middle_y, bottom_middle_x, y2);
    sierpinsky(left_middle_x, left_middle_y, x1, y1, right_middle_x, right_middle_y);
    sierpinsky(bottom_middle_x, y2, right_middle_x, right_middle_y, x2, y2);
  }
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  sierpinsky(0, display.height(), display.width()/2, (display.height()-display.width()), display.width(), display.height());
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

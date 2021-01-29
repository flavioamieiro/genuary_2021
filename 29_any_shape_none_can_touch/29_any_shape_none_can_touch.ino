#include <GxEPD2_BW.h>

#define R 30
#define PADDING 1

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

void polygon(int x, int y, int r, int points) {
  float ang = 2*PI / points;
  int prev_x = x + r;
  int prev_y = y;
  for (float a = ang; a < 2*PI; a += ang) {
    int px = x + cos(a) * r;
    int py = y + sin(a) * r;
    display.drawLine(prev_x, prev_y, px, py, GxEPD_BLACK);
    prev_x = px;
    prev_y = py;
  }
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
    display.fillScreen(GxEPD_WHITE);
  }
  // draw here.
  for (int x=0; x<display.width(); x+=3*R+PADDING) {
    for (int y=0; y<display.height(); y+=R+PADDING) {
      int xx = x+((y % 2)*(1.5*R));
      polygon(xx, y, R, 6);
      display.fillCircle(xx, y, 3*R/5, GxEPD_BLACK);
    }
  }
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;
int minx, maxx, miny, maxy;


void setup() {
  initDisplay();
  minx = 0;
  maxx = display.width();
  miny = 0;
  maxy = display.height();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  fullRefresh();
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
  display.clearScreen();
}

void vline(int x, int starty, int endy) {
  display.drawLine(x, starty, x, endy, GxEPD_BLACK);
}

void hline(int y, int startx, int endx) {
  display.drawLine(startx, y, endx, y, GxEPD_BLACK);
}

void loop() {
  if (loop_count % 2 == 0) {
    int x = random(minx, maxx);
    vline(x, miny, maxy);
    if (random(0, 2) == 0) {
      minx = x;
    } else {
      maxx = x;
    }
  } else {
    int y = random(miny, maxy);
    hline(y, minx, maxx);
    if (random(0, 2) == 0) {
      miny = y;
    } else {
      maxy = y;
    }
  }
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

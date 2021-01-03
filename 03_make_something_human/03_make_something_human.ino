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

void drawFigure(int x, int y) {
  display.drawCircle(x, y, 30, GxEPD_BLACK);
  display.drawLine(x, y+30, x, y+40, GxEPD_BLACK);
  display.drawCircle(x, y+90, 50, GxEPD_BLACK);
  display.drawLine(x+35, y+55, x+75, y, GxEPD_BLACK);
  display.drawLine(x-35, y+55, x-75, y+90, GxEPD_BLACK);
  display.drawLine(x-10, y+139, x-45, y+230, GxEPD_BLACK);
  display.drawLine(x+10, y+139, x+45, y+230, GxEPD_BLACK);
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  int x = random(30, display.width()-80);
  int y = random(30, display.height()-260);
  drawFigure(x, y);
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

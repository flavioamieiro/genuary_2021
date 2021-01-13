#include <GxEPD2_BW.h>

#define R 30

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

int xvel = 10;
int yvel = 10;
int x = 400;
int y = 240;

void setup() {
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  fullRefresh();
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
  display.clearScreen();
}

void loop() {
  loop_count++;
  if (loop_count >= 150) {
    delay(5000);
    return;
  }

  //display.fillScreen(GxEPD_WHITE);
  display.fillCircle(x, y, R, GxEPD_BLACK);
  display.displayWindow(x-R, y-R, x+R, y+R);
  
  x += xvel;
  y += yvel;
  if (x >= display.width() || x <= 0) {
    xvel *= -1;
  }
  if (y >= display.height() || y <= 0) {
    yvel *= -1;
  }
}

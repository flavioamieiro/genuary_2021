#include <GxEPD2_BW.h>
#define BASE_LEN 240
#define MIN_ANGLE PI/36


GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
  f(PI/2);
  display.display();
}

void f(float x) {
  int x_org = display.width() / 2;
  int y_org = display.height() / 2;
  int x_1 = x_org - (int)(BASE_LEN * x * cos(3*PI/4 - x));
  int y_1 = y_org - (int)(BASE_LEN * x * sin(3*PI/4 - x));
  int x_2 = x_org - (int)(BASE_LEN * x * cos(PI/4 - x));
  int y_2 = y_org - (int)(BASE_LEN * x * sin(PI/4 - x));
  int x_3 = x_org - (int)(BASE_LEN * x * cos(7*PI/4 - x));
  int y_3 = y_org - (int)(BASE_LEN * x * sin(7*PI/4 - x));
  int x_4 = x_org - (int)(BASE_LEN * x * cos(5*PI/4 - x));
  int y_4 = y_org - (int)(BASE_LEN * x * sin(5*PI/4 - x));
  display.drawLine(x_1, y_1, x_2, y_2, GxEPD_BLACK);
  //display.drawLine(x_2, y_2, x_3, y_3, GxEPD_BLACK);
  display.drawLine(x_3, y_3, x_4, y_4, GxEPD_BLACK);
  //display.drawLine(x_4, y_4, x_1, y_1, GxEPD_BLACK);
  if (x > MIN_ANGLE) {
    f(1*x/4);
    f(2*x/4);
    f(3*x/4);
  }
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.clearScreen();
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
}

void loop() {}

#include <GxEPD2_BW.h>
#define START_LEN 240
#define RATIO 72
#define ANGLE_STEP PI/RATIO
#define LEN_STEP START_LEN/RATIO
#define MAX_ANGLE 2*PI

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
  draw(0, START_LEN);
  display.display();
}

void draw(float ang, float len) {
  int x_org = display.width() / 2;
  int y_org = display.height() / 2;
  int x_1 = x_org - (int)(len * cos(3*PI/4 - ang));
  int y_1 = y_org - (int)(len * sin(3*PI/4 - ang));
  int x_2 = x_org - (int)(len * cos(PI/4 - ang));
  int y_2 = y_org - (int)(len * sin(PI/4 - ang));
  int x_3 = x_org - (int)(len * cos(7*PI/4 - ang));
  int y_3 = y_org - (int)(len * sin(7*PI/4 - ang));
  int x_4 = x_org - (int)(len * cos(5*PI/4 - ang));
  int y_4 = y_org - (int)(len * sin(5*PI/4 - ang));
  display.drawLine(x_1, y_1, x_2, y_2, GxEPD_BLACK);
  display.drawLine(x_2, y_2, x_3, y_3, GxEPD_BLACK);
  display.drawLine(x_3, y_3, x_4, y_4, GxEPD_BLACK);
  display.drawLine(x_4, y_4, x_1, y_1, GxEPD_BLACK);
  if (ang < MAX_ANGLE) {
    draw(ang + ANGLE_STEP, len - LEN_STEP);
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

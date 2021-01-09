#include <GxEPD2_BW.h>
#define SPACING 25

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  Serial.begin(115200);
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
}

void fullRefresh() {
  display.clearScreen();
  display.fillScreen(GxEPD_WHITE);
}

void vlines(int start_x, int start_y, int linelen) {
  for (int i = 0; i < linelen; i += SPACING) {
    display.drawLine(start_x + i, start_y, start_x + i, start_y + linelen, GxEPD_BLACK);
  }
}

void hlines(int start_x, int start_y, int linelen) {
  for (int i = 0; i < linelen; i += SPACING) {
    display.drawLine(start_x, start_y+i, start_x + linelen, start_y + i, GxEPD_BLACK);
  }
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  for (int i=0; i<=48; i+=3) {
    if (loop_count % 2 == 0) {
      vlines(250+i, 90+i, 300);
    } else {
      hlines(250+i, 90+i, 300);
    }
  }
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

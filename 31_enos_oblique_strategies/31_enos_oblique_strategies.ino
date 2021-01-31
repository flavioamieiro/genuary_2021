#include <GxEPD2_BW.h>

#define STRATEGY "Twist the spine"
#define PADDING 6
#define NUM_LINES 800/PADDING
#define startx 100
#define endx 380

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

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  for (int i=0; i<NUM_LINES; i++) {
    int y = i*PADDING;
    float a = i*6+(loop_count*0.1);
    display.drawLine(startx+PADDING*cos(a), y+PADDING*sin(a), endx+PADDING*cos(a-PI), y+PADDING*sin(a-PI), GxEPD_BLACK);
  }
  display.displayWindow(0, 0, display.width(), display.height());
  delay(1000);
  loop_count++;
}

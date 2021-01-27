#include <GxEPD2_BW.h>
#define PIXEL_SIZE 25
#define COLS (display.width()/PIXEL_SIZE)
#define LINES (display.height()/PIXEL_SIZE)
#define NUM_PIXELS (COLS*LINES)

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();

  int center_col = COLS/2;
  int center_line = LINES/2;

  display.fillScreen(GxEPD_WHITE);
  for (int i=0; i<COLS; i++) {
    int x = PIXEL_SIZE/2 + i * (PIXEL_SIZE);
    for (int j=0; j<LINES; j++) {
      int y = PIXEL_SIZE/2 +  j * (PIXEL_SIZE);
        drawPixel(x, y, map(i+j, 0, (COLS+LINES), 30, 100));
    }
  }
  display.display();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}

void drawPixel(int x, int y, int value) {
  int r = map(value, 0, 100, 0, PIXEL_SIZE/2);
  display.fillCircle(x, y, r, GxEPD_BLACK);
}

void loop() {}

#include <GxEPD2_BW.h>
#include <FastLED.h>
#define PIXEL_SIZE 20
#define NOISE_SCALE 1.5
#define COLS (display.width()/PIXEL_SIZE)
#define LINES (display.height()/PIXEL_SIZE)
#define NUM_PIXELS (COLS*LINES)

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void setup() {
  initDisplay();
  for (int i=0; i<NUM_PIXELS; i++) {
    int col = i % COLS;
    int line = i / COLS;
    int x = PIXEL_SIZE/2 + col * (PIXEL_SIZE);
    int y = PIXEL_SIZE/2 + line * (PIXEL_SIZE);
    int r = inoise8(x*NOISE_SCALE, y*NOISE_SCALE);
    drawPixel(x, y, r);
  }
  display.display();
}

void initDisplay() {
  Serial.begin(115200);
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
}

void drawPixel(int x, int y, int value) {
  int r = map(value, 0, 255, 0, PIXEL_SIZE/2);
  display.fillCircle(x, y, r, GxEPD_BLACK);
}

void loop() {
}

#include <GxEPD2_BW.h>
#include <FastLED.h>

#define NOISE_SCALE 5

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void setup() {
  initDisplay();

  for (int y=0; y<=display.height(); y+=2) {
    draw_line(y, inoise8(y*NOISE_SCALE));
  }
  display.display();
}

void draw_line(int y, uint8_t color) {
  int ratio = display.width() / map(color, 0, 255, 0, display.width());
  for (int x=0; x<=display.width(); x++) {
    int c = (x % ratio == 0) ? GxEPD_BLACK : GxEPD_WHITE;
    display.drawPixel(x, y, c);
  }
}


void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
}

void loop() {}

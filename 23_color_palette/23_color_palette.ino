#include <GxEPD2_BW.h>
#define COLOR_1 0x264653
#define COLOR_2 0x2A9D8F
#define COLOR_3 0xE9C46A
#define COLOR_4 0xF4A261
#define COLOR_5 0xE76F51

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;
uint32_t colors[] = {COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5};

void setup() {
  initDisplay();for (int y=0; y<display.height(); y++) {
    for (int x=0; x<display.width(); x+=21) {
      uint32_t c = colors[random(0, 5)];
      draw_colored_line(c, x, y);
    }
  }
  display.display();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
}

void draw_colored_line(uint32_t c, int x, int y) {
  for (int i=20; i>=0; i--) {
    uint32_t color = ((c & (1 << i)) >> i) ? GxEPD_BLACK : GxEPD_WHITE;
    display.drawPixel(x, y, color);
    x++;
  }
}

void loop() {}

#include <GxEPD2_BW.h>

#define MIN_HEIGHT 50
#define MAX_HEIGHT 150
#define PADDING 0
#define Y_OFF 100
#define W 50
#define ROWS 5

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

float ang = 315*PI/180;

void setup() {
  initDisplay();
  drawSquares();
  display.display();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
}

void drawSquares() {
  int w = display.width();
  int x = 0;
  int y = (display.height() - w)/2;
  int count = 0;
  while (w > 1) {
    display.drawRect(x, y, w, w, GxEPD_BLACK);
    int A = random(0, 10000);
    x += count;
    y += count;
    w -= 20;
    count++;
  }
}

void drawPrisms() {
  int y = (display.height() - (ROWS*Y_OFF));
  for (int i=0; i<ROWS; i++) {
    int cols = random(5, 10);
    int x = (display.width() - (cols*W))/2;
    for (int j=0; j<cols; j++) {
      int h = random(MIN_HEIGHT, MAX_HEIGHT);
      prism(x, y, W, h);
      x += W + PADDING;
    }
    y+=Y_OFF;
  }
}

void prism(int x, int y, int w, int h) {
  int rect_top_y = y-h;
  int rect_right_x = x+w;
  int square_top_left_x = x + w * cos(ang);
  int square_top_y = rect_top_y + w * sin(ang);
  int square_top_right_x = square_top_left_x+w;
  int side_y = square_top_y + h;
  int side_x = x + w + w * cos(ang);
  display.fillTriangle(x, rect_top_y, square_top_left_x, square_top_y, square_top_right_x, square_top_y, GxEPD_WHITE);
  display.fillTriangle(square_top_right_x, square_top_y, x, rect_top_y, rect_right_x, rect_top_y, GxEPD_WHITE);
  display.fillTriangle(square_top_right_x, square_top_y, side_x, side_y, rect_right_x, y, GxEPD_WHITE);
  display.fillTriangle(rect_right_x, rect_top_y, square_top_right_x, square_top_y, rect_right_x, y, GxEPD_WHITE);
  display.fillRect(x, rect_top_y, w, h, GxEPD_WHITE);
  display.drawRect(x, rect_top_y, w, h, GxEPD_BLACK);
  display.drawLine(x, rect_top_y, square_top_left_x, square_top_y, GxEPD_BLACK);
  display.drawLine(square_top_left_x, square_top_y, square_top_right_x, square_top_y, GxEPD_BLACK);
  display.drawLine(rect_right_x, rect_top_y, square_top_right_x, square_top_y, GxEPD_BLACK);
  display.drawLine(square_top_right_x, square_top_y, side_x, side_y, GxEPD_BLACK);
  display.drawLine(rect_right_x, y, side_x, side_y, GxEPD_BLACK);
}

void loop() {}

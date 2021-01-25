#include <GxEPD2_BW.h>
#include <algorithm>

#define NUM_ANGLES 6
#define R 8
#define W 480
#define H 800
#define X_STEP W/(R*2)
#define Y_STEP H/(R*2)

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;
float angles[] = {0, 4, 6, 12, 16, 18};

void setup() {
  initDisplay();
  display.fillScreen(GxEPD_WHITE);
  int x_off = X_STEP/2;
  int y_off = Y_STEP/2;
  do {
    float first_a = (angles[0]*PI)/12;
    int last_x = x_off+(R*cos(first_a));
    int last_y = y_off+(R*sin(first_a));
    for (int i=0; i<NUM_ANGLES; i++) {
      float a = (angles[i]*PI)/12;
      int this_x = x_off+(R*cos(a));
      int this_y = y_off+(R*sin(a));
      display.drawLine(last_x, last_y, this_x, this_y, GxEPD_BLACK);
      last_x = this_x;
      last_y = this_y;
    }
    x_off += X_STEP;
    if (x_off >= display.width()) {
      x_off = X_STEP/2;
      y_off += Y_STEP;
    }
  } while (std::next_permutation(angles, angles+NUM_ANGLES));
  display.display();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
}

void loop() {}

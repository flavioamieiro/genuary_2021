#include <GxEPD2_BW.h>
#include <FastLED.h>
#define HALF_W 240
#define HALF_H 400
#define NUM_LINES 72
#define OFFSET 15
#define NOISE_SCALE 0.1
#define ANGLE_INC (2*PI/NUM_LINES)
#define START_LEN 30
#define MAX_GROWTH 100
//#define DEBUG

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;
int line_lengths[NUM_LINES];

void setup() {
  initDisplay();
  for (int i=0; i<NUM_LINES; i++) {
    line_lengths[i] = START_LEN;
  }
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
}

void fullRefresh() {
  display.clearScreen();
}

void line(float ang, int len) {
  float c = cos(ang);
  float s = sin(ang);
  int start_x = HALF_W + (int)(OFFSET * c);
  int start_y = HALF_H + (int)(OFFSET * s);
  int end_x = HALF_W + (int)((OFFSET + len) * c);
  int end_y = HALF_H + (int)((OFFSET + len) * s);
  display.drawLine(start_x, start_y, end_x, end_y, GxEPD_BLACK);
}

void drawThresh(int thresh) {
  display.drawCircle(HALF_W, HALF_H, OFFSET + thresh, GxEPD_BLACK);
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  int sum = 0;
  for (int i=0; i<NUM_LINES; i++) {
    sum += line_lengths[i];
    line(i * ANGLE_INC, line_lengths[i]);
  }
  float avg = ((float)sum)/NUM_LINES;
  int to_grow = loop_count % NUM_LINES;
  int to_prune = (NUM_LINES - 1) - to_grow;
  line_lengths[to_grow] += random(0, MAX_GROWTH);

  int neigh_1_idx = (to_prune == 0) ? (NUM_LINES - 1) : (to_prune - 1);
  int neigh_2_idx = (to_prune == (NUM_LINES - 1)) ? 0 : to_prune + 1;
  int jitter = map(inoise8(to_prune*NOISE_SCALE, loop_count*NOISE_SCALE), 0, 255, -30, 30);
  float thresh = (((float)line_lengths[neigh_1_idx] + (float)line_lengths[neigh_2_idx])/2.0) + jitter;

  #ifdef DEBUG
  drawThresh((int)thresh);
  #endif

  display.displayWindow(0, 0, display.width(), display.height());
  if (line_lengths[to_prune] > thresh) {
    line_lengths[to_prune] = (int)thresh;
  }
  loop_count++;
}

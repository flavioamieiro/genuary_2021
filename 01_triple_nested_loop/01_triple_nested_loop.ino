#include <GxEPD2_BW.h>
#include "circle.h"

#define MAX_CIRCLES 500
#define MAX_ATTEMPTS 1000

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

int total = 0;
int current_circle_idx = 0;
Circle circles[MAX_CIRCLES];

void setup() {
  Serial.begin(115200);
  initDisplay();
  addNewCircle();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
}

void fullRefresh() {
  display.clearScreen();
}

void addNewCircle() {
  int attempts = 0;
  while (current_circle_idx < MAX_CIRCLES && attempts <= MAX_ATTEMPTS) {
    int r = random(3, 30);
    int x = random(r, display.width() - r);
    int y = random(r, display.height() - r);
    Circle candidate = Circle(x, y, r);
    bool hit = false;
    for(int j=0; j<=current_circle_idx; j++) {
      if (j != current_circle_idx && candidate.hits(circles[j])) {
        hit = true;
      }
    }
    if (!hit) {
      circles[current_circle_idx] = candidate;
      current_circle_idx++;
      total = current_circle_idx;
      break;
    }
    attempts++;
  }
  if (attempts == MAX_ATTEMPTS) {
    Serial.println("Could not add new: max attempts reached.");
  }
  if (current_circle_idx == MAX_CIRCLES) {
    Serial.println("Could not add new: max circles reached.");
  }
}

void loop() {
  if (loop_count % 300 == 0) {
    fullRefresh();
  }

  display.fillScreen(GxEPD_WHITE);
  for (int i=0; i<total; i++){
    Circle& c = circles[i];
    for (int j=0; j<total; j++) {
      if (j == i) {
        continue;
      }
      Circle& other = circles[j];
      if (c.hits(other) || c.hitsEdge()) {
        c.should_grow = false;
        break;
      }
    }
    if (c.should_grow) {
      c.grow();
    }
    display.drawCircle(c.x, c.y, c.r, GxEPD_BLACK);
  }

  display.displayWindow(0, 0, display.width(), display.height());
  addNewCircle();
  loop_count++;
}

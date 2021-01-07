#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define MAX_STEPS 30

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

const char choices[] = "^><";

void setup() {
  initDisplay();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.clearScreen();
  display.fillScreen(GxEPD_WHITE);

  display.setCursor(10, 30);
  display.print("* > - turn right and move forward.");
  display.setCursor(10, 50);
  display.print("* < - turn left and move forward.");
  display.setCursor(10, 70);
  display.print("* ^ - move forward.");
  display.setCursor(10, 90);
  display.print("=================================");
  display.setCursor(10, 110);
}

void loop() {
  if (loop_count == MAX_STEPS) {
    display.print(".");
    display.displayWindow(0, 0, display.width(), display.height());
  } else if (loop_count > MAX_STEPS) {
    delay(1000);
  } else {
    display.print(choices[random(0, 3)]);
    display.print(" ");
    display.displayWindow(0, 0, display.width(), display.height());
  }
  loop_count++;
}

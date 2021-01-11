#include <GxEPD2_BW.h>
#define W 800
#define H 480
#define SIZE 300
#define VPADDING 10
#define HPADDING 10

#define PIN1 13
#define PIN2 12
#define PIN3 14
#define PIN4 21
#define PIN5 15
#define PIN6 19


GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;
int threshold = 40;
bool vertical = false;

int box_size = SIZE;
int x1 = 65;
int x2 = 195;
int x3 = 325;
int x4 = 455;
int x5 = 585;
int x6 = 715;
int y = 0;

void setup() {
  Serial.begin(115200);
  initDisplay();
  pinMode(PIN1, INPUT_PULLUP);
  pinMode(PIN2, INPUT_PULLUP);
  pinMode(PIN3, INPUT_PULLUP);
  pinMode(PIN4, INPUT_PULLUP);
  pinMode(PIN5, INPUT_PULLUP);
  pinMode(PIN6, INPUT_PULLUP);
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  fullRefresh();
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
  display.clearScreen();
}

void loop() {
  if (digitalRead(PIN1) == LOW) {
    Serial.println("Hit 1");
    rect(x1, y);
  } else if (digitalRead(PIN2) == LOW) {
    Serial.println("Hit 2");
    rect(x2, y);
  } else if (digitalRead(PIN3) == LOW) {
    Serial.println("Hit 3");
    rect(x3, y);
  } else if (digitalRead(PIN4) == LOW) {
    Serial.println("Hit 4");
    rect(x4, y);
  } else if (digitalRead(PIN5) == LOW) {
    Serial.println("Hit 5");
    rect(x5, y);
  } else if (digitalRead(PIN6) == LOW) {
    Serial.println("Hit 6");
    rect(x6, y);
  }
  y += VPADDING;
  if (y > display.height()) {
    y = 0;
  }
  loop_count++;
}

void rect(int x, int y) {
  if (vertical) {
    int start_y = y - SIZE/2;
    int end_y = y + SIZE/2;
    display.drawLine(x, start_y, x, end_y, GxEPD_BLACK);
    vertical = false;
  } else {
    int start_x = x - SIZE/2;
    int end_x = x + SIZE/2;
    display.drawLine(start_x, y, end_x, y, GxEPD_BLACK);
    vertical = true;
  }
  display.displayWindow(0, 0, display.width(), display.height());
}

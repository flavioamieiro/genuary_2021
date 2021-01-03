#include <GxEPD2_BW.h>

#define H 480
#define W 800
#define CELL_SIDE 8
#define NUM_CELLS (W/CELL_SIDE)
#define TAPE_SIZE (NUM_CELLS*2)  // "Infinite" tape

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

bool tape[TAPE_SIZE];

void setup() {
  initDisplay();
  initializeTape();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
}

void fullRefresh() {
  display.clearScreen();
}

void initializeTape() {
  for (int i=0; i<TAPE_SIZE; i++) {
    bool state = false;
    if (random(0, 10) < 2) {
      state = true;
    }
    // if (i == 80) state = true;
    tape[i] = state;
  }
}

bool evaluate(bool left, bool center, bool right) {
  return (left ^ (center || right));
}

void updateTape() {
  bool new_tape[TAPE_SIZE];

  new_tape[0] = evaluate(false, tape[0], tape[1]);
  for (int i=1; i < (TAPE_SIZE-1); i++) {
    new_tape[i] = evaluate(tape[i-1], tape[i], tape[i+1]);
  }
  new_tape[TAPE_SIZE-1] = evaluate(tape[TAPE_SIZE-2], tape[TAPE_SIZE-1], false);

  for (int i=0; i < TAPE_SIZE; i++) {
    tape[i] = new_tape[i];
  }
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }

  int current_line = loop_count % (H/CELL_SIDE);
  int first_cell = 30;
  for (int i=first_cell; i < (first_cell+NUM_CELLS); i++) {
    uint16_t color = tape[i] ? GxEPD_BLACK : GxEPD_WHITE;
    int x = i - first_cell;
    display.fillRect(x*CELL_SIDE, current_line*CELL_SIDE, CELL_SIDE, CELL_SIDE, color);
  }

  display.displayWindow(0, 0, display.width(), display.height());
  updateTape();

  loop_count++;
}

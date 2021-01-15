#include <GxEPD2_BW.h>
#include <esp_spi_flash.h>

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

void displayFlash() {
  unsigned long addr = 0;
  unsigned long rem = ESP.getSketchSize();
  uint8_t *data = new uint8_t[SPI_FLASH_SEC_SIZE];
  int sz = SPI_FLASH_SEC_SIZE;

  int x = 0;
  int y = 0;
  while (rem > 0) {
      ESP.flashRead(addr, (uint32_t *)data, SPI_FLASH_SEC_SIZE);
      for (int i=0; i<SPI_FLASH_SEC_SIZE; i++) {
        uint32_t d = data[i];
        for (int j=sizeof(d)-1; j>=0; j--) {
          uint32_t color = ((d & (1 << j)) >> j) ? GxEPD_BLACK : GxEPD_WHITE;
          display.drawPixel(x, y, color);
          x++;
          if (x > display.width()) {
            x = 0;
            y += 1;
          }
        }
      }
      if (rem < sz)
          sz = rem;
      addr += SPI_FLASH_SEC_SIZE;
      rem -= sz;
      yield();
  }
}



void setup() {
  display.init(0, true, 2, false);
  display.setRotation(1);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  displayFlash();
  display.display(false);
}

void loop() {}

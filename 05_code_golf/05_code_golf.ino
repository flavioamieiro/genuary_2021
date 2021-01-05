#include <GxEPD2_BW.h>
#define M 200
#define C (c%M)
#define S (C-M)*2
#define T C*10
#define w d.width()
#define h d.height()
GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> d(GxEPD2_750_T7(SS,17,16,4));int c=0;void setup(){d.init(0,true,2,false);d.setRotation(0);d.clearScreen();d.fillScreen(0xFF);}void loop(){d.drawLine(S,T,w-S,h-T,0);d.displayWindow(0,0,w,h);c++;}

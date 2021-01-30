#include <GxEPD2_BW.h>
#include "particle.h"
#define NUM_PARTICLES 1
#define PLANET_RADIUS 100
#define G 2

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
int loop_count = 0;

Particle particles[NUM_PARTICLES];
Particle planet;

void setup() {
  initDisplay();
  initParticles();
  planet = Particle(display.width()/2, display.height()/2, 50);
}

void initParticles() {
  for (int i=0; i<NUM_PARTICLES; i++) {
    Particle p(random(300, W-300), random(150, H-150), 10);
    particles[i] = p;
  }
};


void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
}

void fullRefresh() {
  display.clearScreen();
}

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }
  display.fillScreen(GxEPD_WHITE);
  showParticle(planet);

  for (int i=0; i<NUM_PARTICLES; i++) {
    Particle& moon = particles[i];
    moon.update();
    showParticle(moon);
    int dx = planet.x - moon.x;
    int dy = planet.y - moon.y;
    float d = sqrt((dx*dx + dy*dy));
    float gravity = G * (moon.mass * planet.mass) / (d*d);
    float a = atan2(dy, dx);
    a = (a < 0) ? (2*PI + a) : a;
    moon.applyForce(min((int)gravity, 5), a);
  }
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

void showParticle(Particle a) {
  display.fillCircle(a.x, a.y, a.r, GxEPD_BLACK);
}

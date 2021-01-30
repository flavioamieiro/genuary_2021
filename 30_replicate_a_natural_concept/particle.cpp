#include <math.h>
#include <stdlib.h>
#include <Arduino.h>
#include "particle.h"

Particle::Particle() { };

Particle::Particle(int x_, int y_, int r_) {
  x = x_;
  y = y_;
  r = r_;
  mass = r_*r_;
  velx = 0;
  vely = 0;
};

void Particle::update() {
  x += velx;
  y += vely;
  constrain(velx, 0, 10);
  constrain(vely, 0, 10);
};

void Particle::applyForce(int f, float angle) {
  if (abs(velx) < max_speed) {
    velx += f * cos(angle);
  };
  if (abs(vely) < max_speed) {
    vely += f * sin(angle);
  };
};

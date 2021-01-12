#include <math.h>
#include <stdlib.h>
#include "particle.h"

Particle::Particle() { };

Particle::Particle(int x_, int y_) {
  x = x_;
  y = y_;
  r = 10;
  velx = 0;
  vely = 0;
};

void Particle::update() {
  x += velx;
  y += vely;
  if (x > W) {
    x = 0;
  } else if (x < 0) {
    x = W;
  };

  if (y > H) {
    y = 0;
  } else if (y < 0) {
    y = H;
  };
};

void Particle::applyForce(int f, float angle) {
  if (abs(velx) < max_speed) {
    velx += f * cos(angle);
  };
  if (abs(vely) < max_speed) {
    vely += f * sin(angle);
  };
};

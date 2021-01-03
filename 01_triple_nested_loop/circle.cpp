#include <Arduino.h>
#include <math.h>
#include "circle.h"

#define WIDTH 480
#define HEIGHT 800
#define TOLERANCE 5

Circle::Circle() {};

Circle::Circle(int _x, int _y, int _r) {
  r = _r;
  x = _x;
  y = _y;
  int i = 0;
};

void Circle::grow() {
  r *= 1.2;
}

bool Circle::hits(Circle other) {
  int dist = hypot(other.x - x, other.y - y); 
  return (dist - (r*0.2) < r + other.r);
};

bool Circle::hitsEdge() {
  return (x - r - (r*0.2) - 1 <= 0) || (x + r + (r*0.2) + 1 >= WIDTH) || (y - r - (r*0.2) - 1 <= 0) || (y + r + (r*0.2) + 1 >= HEIGHT); 
}

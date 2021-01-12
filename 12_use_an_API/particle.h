#define MAX_SPEED 30
#define W 800
#define H 480

#define PI 3.14159265

class Particle {
  public:
    Particle();
    Particle(int x_, int y_);
    int x;
    int y;
    int r = 8;
    int velx = 0;
    int vely = 0;
    int max_speed = MAX_SPEED;
    void update();
    void applyForce(int f, float angle);
};

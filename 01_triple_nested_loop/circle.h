class Circle {
  public:
    Circle();
    Circle(int max_x, int max_y, int max_r);
    int x;
    int y;
    int r;
    bool should_grow = true;
    void grow();
    bool hits(Circle other);
    bool hitsEdge();
};

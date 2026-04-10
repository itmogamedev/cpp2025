class Circle {
 private:
  float x, y;
  float radius;
  sf::Vector2f velocity;
  float speed;
  sf::CircleShape circle;
  sf::Color color;

 public:
  Circle();

  int getX() const { return x; }
  int getY() const { return y; }
  int getRadius() const { return radius; }
  sf::CircleShape getCircle() const { return circle; }

  void setX(int newX) { x = newX; }
  void setY(int newY) { y = newY; }
  void setRadius(int newRadius) { radius = newRadius; }

  bool checksCollision(int mouseX, int mouseY);
  void move();
  void updateCircle();
};
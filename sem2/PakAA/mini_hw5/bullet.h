#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
 public:
  Bullet(float x, float y);

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;

  sf::FloatRect getBounds() const;
  // True, если снаряд улетел за верхний край окна.
  bool isOffScreen() const;

 private:
  sf::RectangleShape shape;
  float speed;
};

#endif  // SPACE_SHOOTER_BULLET_H

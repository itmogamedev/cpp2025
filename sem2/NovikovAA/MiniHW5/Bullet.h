#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
 private:
  sf::RectangleShape shape;
  float speed;

 public:
  Bullet(float x, float y);

  void update(float dt);

  void draw(sf::RenderWindow& window);

  sf::FloatRect getBounds() const;

  float getY() const;
};

#endif

#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet {
 public:
  Bullet(float x, float y);

  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  sf::FloatRect getBounds() const;
  bool isOffScreen(float windowHeight) const;

 private:
  sf::RectangleShape shape;
  float speed;
};
#endif

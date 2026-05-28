#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>

class Asteroid {
 public:
  Asteroid(float x, float y, float speed);

  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  sf::FloatRect getBounds() const;
  bool isOffScreen(float windowHeight) const;

 private:
  sf::CircleShape shape;
  float speed;
};
#endif
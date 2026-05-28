#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid {
 private:
  sf::CircleShape shape;
  float speed;

 public:
  Asteroid(float x, float speed);

  void update(float dt);

  void draw(sf::RenderWindow& window);

  sf::FloatRect getBounds() const;

  float getY() const;
};

#endif

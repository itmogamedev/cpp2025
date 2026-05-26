#ifndef MININHWLAST_ASTEROID_H
#define MININHWLAST_ASTEROID_H

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Asteroid {
public:
  sf::RectangleShape shape;
  float speed;

  Asteroid(float x, float speed, float size);
  void tick(std::shared_ptr<sf::RenderWindow> rend, float dt);
  bool isOutOfBounds(float windowHeight) const;
};

#endif // MININHWLAST_ASTEROID_H

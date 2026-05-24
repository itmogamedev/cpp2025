#ifndef MININHWLAST_LASER_H
#define MININHWLAST_LASER_H

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Laser {
public:
  sf::RectangleShape shape;
  float speed;

  Laser(float x, float y, float speed);
  void tick(std::shared_ptr<sf::RenderWindow> rend, float dt);
  bool isOutOfBounds() const;
};

#endif // MININHWLAST_LASER_H

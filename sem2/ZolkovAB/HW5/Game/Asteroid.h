#pragma once
#include <SFML/Graphics.hpp>

class Asteroid {
 private:
  sf::RectangleShape shape;
  float movementSpeed;

 public:
  Asteroid(float posX, float speed);
  void update();
  void render(sf::RenderTarget& target) const;
  sf::FloatRect getBounds() const;
  float getPositionY() const;
};
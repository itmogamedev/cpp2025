#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
 private:
  sf::RectangleShape shape;
  float movementSpeed;

 public:
  Bullet(float posX, float posY);
  void update();
  void render(sf::RenderTarget& target) const;
  sf::FloatRect getBounds() const;
  float getPositionY() const;
};
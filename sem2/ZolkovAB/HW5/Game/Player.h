#pragma once
#include <SFML/Graphics.hpp>

class Player {
 private:
  sf::RectangleShape shape;
  float movementSpeed;

 public:
  Player();
  void update();
  void render(sf::RenderTarget& target) const;
  sf::FloatRect getBounds() const;
  sf::Vector2f getPosition() const;
};
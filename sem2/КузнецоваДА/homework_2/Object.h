#pragma once
#include <SFML/Graphics.hpp>

class Object {
 public:
  int size;
  sf::Vector2f circlePos;
  sf::CircleShape shape;
  sf::Vector2f speed;

  Object(int size, sf::Vector2f circlePos);

  void updatePos(float frame);
  void setPos(sf::Vector2f newCirclePos);
  void setSpeed(sf::Vector2f newSpeed);
  void draw(sf::RenderWindow& window);
  bool nearCursor(sf::Vector2f& mousePos);
};

#pragma once
#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(float radius);

  void setRandomPosition(int maxX, int maxY);
  void setRandomVelocity(float minSpeed, float maxSpeed);
  void update(float dt, int maxX, int maxY);
  void draw(sf::RenderWindow& window);
  bool isClicked(sf::Vector2i mousePos);

 private:
  sf::CircleShape shape;
  sf::Vector2f velocity;
};

#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(float radius, sf::Vector2u windowSize);

  void update(float dt);
  void draw(sf::RenderWindow& window);
  bool contains(sf::Vector2f point);

  void respawn(sf::Vector2u windowSize);

 private:
  sf::CircleShape shape_;
  sf::Vector2f velocity_;
};

#endif
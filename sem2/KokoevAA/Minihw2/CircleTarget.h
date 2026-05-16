#ifndef CIRCLETARGET_H
#define CIRCLETARGET_H

#include <SFML/Graphics.hpp>

class CircleTarget {
 public:
  CircleTarget();

  void update(const sf::RenderWindow& window, float delta_time);
  void draw(sf::RenderWindow& window) const;

  bool containsPoint(const sf::Vector2f& point) const;
  void setRandomPosition(const sf::RenderWindow& window);
  void setRandomVelocity();

 private:
  sf::CircleShape shape;
  sf::Vector2f velocity;
};

#endif

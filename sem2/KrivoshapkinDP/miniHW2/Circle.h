#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(float radius, const sf::Color& color, const sf::Vector2f& position,
         const sf::Vector2f& velocity);
  void update(float deltaTime, const sf::Vector2u& windowSize);
  void draw(sf::RenderWindow& window) const;
  bool contains(const sf::Vector2f& point) const;
  void setPosition(const sf::Vector2f& position);
  sf::Vector2f getPosition() const;

 private:
  sf::CircleShape shape;
  sf::Vector2f velocity;
  float radius;
};

#endif

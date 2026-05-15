#pragma once
#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(const sf::Vector2f& position, float radius);
  void draw(sf::RenderWindow& window) const;
  bool contains(const sf::Vector2f& point) const;
  void setPosition(const sf::Vector2f& position);
  void update(float deltaTime, float windowWidth, float windowHeight);
  void resetVelocity();

 private:
  sf::CircleShape m_shape;
  float m_radius;
  sf::Vector2f m_velocity;
  float m_timeToChangeDir;
};

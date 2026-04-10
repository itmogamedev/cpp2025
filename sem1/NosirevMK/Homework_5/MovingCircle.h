#ifndef MOVING_CIRCLE_H
#define MOVING_CIRCLE_H

#include <SFML/Graphics.hpp>

class MovingCircle {
 public:
  MovingCircle(float radius, const sf::Vector2f& startPos,
               const sf::Vector2f& startVelocity, const sf::Color& color);

  void update(float deltaTime, const sf::Vector2u& windowSize);

  void draw(sf::RenderWindow& window);

  bool isClicked(const sf::Vector2i& mousePos) const;

  void teleportToRandomPosition(const sf::Vector2u& windowSize);

  void setRandomVelocity();

  sf::Vector2f getPosition() const;
  sf::Vector2f getVelocity() const;
  sf::Color getColor() const;

 private:
  sf::CircleShape m_circle;
  sf::Vector2f m_velocity;
  float m_radius;
};

#endif

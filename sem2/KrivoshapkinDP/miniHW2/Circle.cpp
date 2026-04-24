#include "Circle.h"

#include <algorithm>

Circle::Circle(float radius, const sf::Color& color,
               const sf::Vector2f& position, const sf::Vector2f& velocity)
    : radius(radius), velocity(velocity) {
  shape.setRadius(radius);
  shape.setFillColor(color);
  shape.setOrigin({radius, radius});
  shape.setPosition(position);
}

void Circle::update(float deltaTime, const sf::Vector2u& windowSize) {
  sf::Vector2f position = shape.getPosition();
  position += velocity * deltaTime;

  if (position.x - radius < 0 || position.x + radius > windowSize.x) {
    velocity.x = -velocity.x;
    position.x = std::clamp(position.x, radius,
                            static_cast<float>(windowSize.x) - radius);
  }

  if (position.y - radius < 0 || position.y + radius > windowSize.y) {
    velocity.y = -velocity.y;
    position.y = std::clamp(position.y, radius,
                            static_cast<float>(windowSize.y) - radius);
  }

  shape.setPosition(position);
}

void Circle::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool Circle::contains(const sf::Vector2f& point) const {
  sf::Vector2f center = shape.getPosition();
  float dx = point.x - center.x;
  float dy = point.y - center.y;
  return (dx * dx + dy * dy) <= (radius * radius);
}

void Circle::setPosition(const sf::Vector2f& position) {
  shape.setPosition(position);
}

sf::Vector2f Circle::getPosition() const { return shape.getPosition(); }

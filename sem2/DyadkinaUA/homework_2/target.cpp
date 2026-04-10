#include "target.h"

CircleTarget::CircleTarget(float radius, const sf::Color& color)
    : shape(radius) {
  shape.setFillColor(color);
  shape.setOutlineThickness(3.0f);
  shape.setOutlineColor(sf::Color::White);
  shape.setOrigin({radius, radius});
}

void CircleTarget::setPosition(const sf::Vector2f& position) {
  shape.setPosition(position);
}

void CircleTarget::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool CircleTarget::contains(const sf::Vector2f& point) const {
  const sf::Vector2f center = shape.getPosition();
  const float dx = point.x - center.x;
  const float dy = point.y - center.y;
  const float radius = shape.getRadius();
  return dx * dx + dy * dy <= radius * radius;
}

float CircleTarget::getRadius() const { return shape.getRadius(); }

sf::Vector2f CircleTarget::getPosition() const { return shape.getPosition(); }

#include "Circle.h"
#include <cstdlib>

Circle::Circle(float radius, sf::Vector2u windowSize) {
  shape_.setRadius(radius);
  shape_.setFillColor(sf::Color::Green);

  respawn(windowSize);

  velocity_.x = (std::rand() % 200 - 100);
  velocity_.y = (std::rand() % 200 - 100);
}

void Circle::update(float dt) {
  shape_.move(velocity_ * dt);

  sf::Vector2f pos = shape_.getPosition();
  float r = shape_.getRadius();

  if (pos.x <= 0 || pos.x + r * 2 >= 800) velocity_.x *= -1;
  if (pos.y <= 0 || pos.y + r * 2 >= 600) velocity_.y *= -1;
}

void Circle::draw(sf::RenderWindow& window) {
  window.draw(shape_);
}

bool Circle::contains(sf::Vector2f point) {
  return shape_.getGlobalBounds().contains(point);
}

void Circle::respawn(sf::Vector2u windowSize) {
  float x = std::rand() % (windowSize.x - 50);
  float y = std::rand() % (windowSize.y - 50);
  shape_.setPosition(x, y);
}
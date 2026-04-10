#include "circle.h"

#include <cmath>
#include <cstdlib>

Circle::Circle(float window_width, float window_height) {
  radius = CIRCLE_RADIUS;
  shape.setRadius(radius);
  shape.setOrigin(sf::Vector2f(radius, radius));
  shape.setFillColor(CIRCLE_COLOR);

  shape.setPosition(sf::Vector2f(
      static_cast<float>(rand() % static_cast<int>(window_width)),
      static_cast<float>(rand() % static_cast<int>(window_height))));

  velocity.x = static_cast<float>((rand() % VELOCITY_RANGE) + VELOCITY_MIN);
  velocity.y = static_cast<float>((rand() % VELOCITY_RANGE) + VELOCITY_MIN);
}

void Circle::update(float dt, float window_width, float window_height) {
  sf::Vector2f pos = shape.getPosition();
  pos += velocity * dt;

  if (pos.x < radius || pos.x > window_width - radius) {
    velocity.x = -velocity.x;
  }
  if (pos.y < radius || pos.y > window_height - radius) {
    velocity.y = -velocity.y;
  }

  shape.setPosition(pos);
}

void Circle::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool Circle::isClicked(const sf::Vector2i& mouse_pos) const {
  sf::Vector2f circle_pos = shape.getPosition();
  float dx = static_cast<float>(mouse_pos.x) - circle_pos.x;
  float dy = static_cast<float>(mouse_pos.y) - circle_pos.y;
  return std::sqrt(dx * dx + dy * dy) < radius;
}

void Circle::reposition(float window_width, float window_height) {
  shape.setPosition(sf::Vector2f(
      static_cast<float>(rand() % static_cast<int>(window_width)),
      static_cast<float>(rand() % static_cast<int>(window_height))));

  velocity.x = static_cast<float>((rand() % VELOCITY_RANGE) + VELOCITY_MIN);
  velocity.y = static_cast<float>((rand() % VELOCITY_RANGE) + VELOCITY_MIN);
}

#include "CircleTarget.h"

#include <cstdlib>

CircleTarget::CircleTarget() {
  shape.setRadius(30.0f);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition({100.0f, 100.0f});
  setRandomVelocity();
}

void CircleTarget::update(const sf::RenderWindow& window, float dt) {
  shape.move(velocity * dt);

  sf::Vector2f pos = shape.getPosition();
  float d = shape.getRadius() * 2.0f;

  float w = static_cast<float>(window.getSize().x);
  float h = static_cast<float>(window.getSize().y);

  if (pos.x <= 0 || pos.x + d >= w) velocity.x = -velocity.x;
  if (pos.y <= 0 || pos.y + d >= h) velocity.y = -velocity.y;
}

void CircleTarget::draw(sf::RenderWindow& window) const { window.draw(shape); }

bool CircleTarget::containsPoint(const sf::Vector2f& p) const {
  sf::Vector2f c =
      shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());

  float dx = p.x - c.x;
  float dy = p.y - c.y;

  return dx * dx + dy * dy <= shape.getRadius() * shape.getRadius();
}

void CircleTarget::setRandomPosition(const sf::RenderWindow& window) {
  float d = shape.getRadius() * 2.0f;

  float max_x = static_cast<float>(window.getSize().x) - d;
  float max_y = static_cast<float>(window.getSize().y) - d;

  float x = static_cast<float>(std::rand()) / RAND_MAX * max_x;
  float y = static_cast<float>(std::rand()) / RAND_MAX * max_y;

  shape.setPosition({x, y});
}

void CircleTarget::setRandomVelocity() {
  float vx = 150 + std::rand() % 200;
  float vy = 150 + std::rand() % 200;

  if (std::rand() % 2) vx = -vx;
  if (std::rand() % 2) vy = -vy;

  velocity = {vx, vy};
}

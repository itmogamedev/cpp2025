#include "MovingCircle.h"

#include <algorithm>
#include <cmath>

MovingCircle::MovingCircle(float x, float y, sf::Vector2f velocity,
                           sf::Vector2f field_size, float radius)
    : shape(radius), velocity(velocity), field_size(field_size) {
  shape.setOrigin(sf::Vector2f(radius, radius));
  shape.setPosition(sf::Vector2f(x, y));
  shape.setFillColor(sf::Color(100, 200, 250));
}
sf::Vector2f MovingCircle::getPosition() const { return shape.getPosition(); }

void MovingCircle::setPosition(const sf::Vector2f& pos) {
  shape.setPosition(pos);
}

void MovingCircle::setVelocity(const sf::Vector2f& vel) { velocity = vel; }
sf::Vector2f MovingCircle::getVelocity() const { return velocity; }

const sf::Shape& MovingCircle::getShape() const { return shape; }

void MovingCircle::move(float dt) {
  sf::Vector2f p = getPosition();
  p += velocity * dt;
  float r = shape.getRadius();
  if (p.x - r < 0.f) {
    p.x = r;
    velocity.x = std::abs(velocity.x);
  }
  if (p.x + r > field_size.x) {
    p.x = field_size.x - r;
    velocity.x = -std::abs(velocity.x);
  }
  if (p.y - r < 0.f) {
    p.y = r;
    velocity.y = std::abs(velocity.y);
  }
  if (p.y + r > field_size.y) {
    p.y = field_size.y - r;
    velocity.y = -std::abs(velocity.y);
  }
  setPosition(p);
}

bool MovingCircle::hit(const sf::Vector2f& point) const {
  sf::Vector2f pos = getPosition();
  float dx = point.x - pos.x;
  float dy = point.y - pos.y;
  float dist2 = dx * dx + dy * dy;
  float r = shape.getRadius();
  return dist2 <= r * r;
}

bool MovingCircle::teleportIfHit(const sf::Vector2f& point,
                                 RandomGenerator& randGen) {
  if (!hit(point)) return false;
  float r = shape.getRadius();
  float nx = std::clamp(randGen.randomX(), r, field_size.x - r);
  float ny = std::clamp(randGen.randomY(), r, field_size.y - r);
  setPosition(sf::Vector2f(nx, ny));
  velocity = sf::Vector2f(randGen.randomVelocity(), randGen.randomVelocity());
  return true;
}

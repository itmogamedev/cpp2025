#include "MovingCircle.h"

#include <cmath>
#include <cstdlib>

MovingCircle::MovingCircle(float radius, const sf::Vector2f& startPos,
                           const sf::Vector2f& startVelocity,
                           const sf::Color& color)
    : m_radius(radius), m_velocity(startVelocity) {
  m_circle.setRadius(radius);
  m_circle.setFillColor(color);
  m_circle.setOrigin({radius, radius});
  m_circle.setPosition(startPos);
}

void MovingCircle::update(float deltaTime, const sf::Vector2u& windowSize) {
  sf::Vector2f newPos = m_circle.getPosition() + m_velocity * deltaTime;

  if (newPos.x - m_radius <= 0.f) {
    newPos.x = m_radius;
    m_velocity.x = -m_velocity.x;
  } else if (newPos.x + m_radius >= static_cast<float>(windowSize.x)) {
    newPos.x = static_cast<float>(windowSize.x) - m_radius;
    m_velocity.x = -m_velocity.x;
  }

  if (newPos.y - m_radius <= 0.f) {
    newPos.y = m_radius;
    m_velocity.y = -m_velocity.y;
  } else if (newPos.y + m_radius >= static_cast<float>(windowSize.y)) {
    newPos.y = static_cast<float>(windowSize.y) - m_radius;
    m_velocity.y = -m_velocity.y;
  }

  m_circle.setPosition(newPos);
}

void MovingCircle::draw(sf::RenderWindow& window) { window.draw(m_circle); }

bool MovingCircle::isClicked(const sf::Vector2i& mousePos) const {
  sf::Vector2f circlePos = m_circle.getPosition();
  float dx = static_cast<float>(mousePos.x) - circlePos.x;
  float dy = static_cast<float>(mousePos.y) - circlePos.y;
  float distance = std::sqrt(dx * dx + dy * dy);

  return distance <= m_radius;
}

void MovingCircle::teleportToRandomPosition(const sf::Vector2u& windowSize) {
  float minX = m_radius;
  float maxX = static_cast<float>(windowSize.x) - m_radius;
  float minY = m_radius;
  float maxY = static_cast<float>(windowSize.y) - m_radius;

  float newX = minX + static_cast<float>(std::rand()) /
                          (static_cast<float>(RAND_MAX) / (maxX - minX));
  float newY = minY + static_cast<float>(std::rand()) /
                          (static_cast<float>(RAND_MAX) / (maxY - minY));

  m_circle.setPosition({newX, newY});
}

void MovingCircle::setRandomVelocity() {
  float speedX = -300.f + static_cast<float>(std::rand()) /
                              (static_cast<float>(RAND_MAX) / 600.f);
  float speedY = -300.f + static_cast<float>(std::rand()) /
                              (static_cast<float>(RAND_MAX) / 600.f);

  if (std::abs(speedX) < 50.f) speedX = (speedX > 0.f) ? 120.f : -120.f;
  if (std::abs(speedY) < 50.f) speedY = (speedY > 0.f) ? 120.f : -120.f;

  m_velocity = {speedX, speedY};
}

sf::Vector2f MovingCircle::getPosition() const {
  return m_circle.getPosition();
}

sf::Vector2f MovingCircle::getVelocity() const { return m_velocity; }

sf::Color MovingCircle::getColor() const { return m_circle.getFillColor(); }

#include "Circle.h"

#include <cmath>
#include <cstdlib>

#include "Constants.h"

Circle::Circle(const sf::Vector2f& position, float radius)
    : m_radius(radius), m_velocity(0.f, 0.f), m_timeToChangeDir(0.f) {
  m_shape.setRadius(radius);
  m_shape.setFillColor(sf::Color(CIRCLE_COLOR_R, CIRCLE_COLOR_G, CIRCLE_COLOR_B,
                                 CIRCLE_COLOR_A));
  m_shape.setOrigin({radius, radius});
  m_shape.setPosition(position);
  resetVelocity();
}

void Circle::draw(sf::RenderWindow& window) const { window.draw(m_shape); }

bool Circle::contains(const sf::Vector2f& point) const {
  sf::Vector2f center = m_shape.getPosition();
  float dx = point.x - center.x;
  float dy = point.y - center.y;
  return (dx * dx + dy * dy) <= (m_radius * m_radius);
}

void Circle::setPosition(const sf::Vector2f& position) {
  m_shape.setPosition(position);
}

void Circle::update(float deltaTime, float windowWidth, float windowHeight) {
  m_timeToChangeDir -= deltaTime;
  if (m_timeToChangeDir <= 0.f) {
    resetVelocity();
  }

  sf::Vector2f newPos = m_shape.getPosition() + m_velocity * deltaTime;
  if (newPos.x - m_radius < 0) {
    newPos.x = m_radius;
    m_velocity.x = -m_velocity.x;
  }
  if (newPos.x + m_radius > windowWidth) {
    newPos.x = windowWidth - m_radius;
    m_velocity.x = -m_velocity.x;
  }
  if (newPos.y - m_radius < 0) {
    newPos.y = m_radius;
    m_velocity.y = -m_velocity.y;
  }
  if (newPos.y + m_radius > windowHeight) {
    newPos.y = windowHeight - m_radius;
    m_velocity.y = -m_velocity.y;
  }
  m_shape.setPosition(newPos);
}

void Circle::resetVelocity() {
  float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.f;
  float speed = CIRCLE_MIN_SPEED;
  m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
  m_timeToChangeDir = CIRCLE_DIRECTION_CHANGE_INTERVAL_MIN +
                      static_cast<float>(rand()) / RAND_MAX *
                          (CIRCLE_DIRECTION_CHANGE_INTERVAL_MAX -
                           CIRCLE_DIRECTION_CHANGE_INTERVAL_MIN);
}

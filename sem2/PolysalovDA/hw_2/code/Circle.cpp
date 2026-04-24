#include "Circle.h"

#include "Constants.h"
Circle::Circle(float r) : radius(r), active(true) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Green);
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(CIRCLES_OUTLINE_THICKNESS);
  shape.setOrigin(sf::Vector2f(radius, radius));
}

void Circle::setRandomPosition(const sf::Vector2u& window_size) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist_x(radius, window_size.x - radius);
  std::uniform_real_distribution<float> dist_y(radius, window_size.y - radius);

  position = sf::Vector2f(dist_x(gen), dist_y(gen));
  shape.setPosition(position);
}

void Circle::setPosition(const sf::Vector2f& pos) {
  position = pos;
  shape.setPosition(position);
}

bool Circle::isOverlapping(const Circle& other) const {
  if (!other.active) return false;

  float dx = position.x - other.position.x;
  float dy = position.y - other.position.y;
  float distance = std::sqrt(dx * dx + dy * dy);

  return distance < (radius + other.radius);
}

bool Circle::containsPoint(const sf::Vector2i& point) const {
  sf::Vector2f mouse_pos(point.x, point.y);
  return active && (std::hypot(mouse_pos.x - position.x,
                               mouse_pos.y - position.y) <= radius);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (active) {
    target.draw(shape, states);
  }
}

void Circle::setRandomVelocity() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_real_distribution<float> speed_dist(SPEED_DIST_MIN,
                                                   SPEED_DIST_MAX);
  std::uniform_real_distribution<float> angle_dist(ANGLE_DIST_MIN,
                                                   ANGLE_DIST_MAX);

  float speed = speed_dist(gen);
  float angle = angle_dist(gen);

  velocity.x = std::cos(angle) * speed;
  velocity.y = std::sin(angle) * speed;
}

void Circle::update(float delta_time, const sf::Vector2u& window_size) {
  if (!active) return;

  position += velocity * delta_time;

  if (position.x - radius < 0) {
    position.x = radius;
    velocity.x = -velocity.x;
  }
  if (position.x + radius > window_size.x) {
    position.x = window_size.x - radius;
    velocity.x = -velocity.x;
  }
  if (position.y - radius < 0) {
    position.y = radius;
    velocity.y = -velocity.y;
  }
  if (position.y + radius > window_size.y) {
    position.y = window_size.y - radius;
    velocity.y = -velocity.y;
  }

  shape.setPosition(position);
}
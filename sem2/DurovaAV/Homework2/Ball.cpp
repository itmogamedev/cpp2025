#include "Ball.h"

#include <cstdlib>

static float randomRange(float low, float high) {
  return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                   (high - low);
}

Ball::Ball(float radius) {
  body_.setRadius(radius);
  body_.setFillColor(sf::Color::Red);
  body_.setOutlineColor(sf::Color::Yellow);
  body_.setOutlineThickness(3.0f);
}

void Ball::setRandomSpawn(int maxWidth, int maxHeight) {
  float radius = body_.getRadius();
  float x =
      static_cast<float>(rand() % (maxWidth - static_cast<int>(2 * radius)));
  float y =
      static_cast<float>(rand() % (maxHeight - static_cast<int>(2 * radius)));
  body_.setPosition(x, y);
}

void Ball::setRandomMovement(float minSpeed, float maxSpeed) {
  float vx = randomRange(minSpeed, maxSpeed);
  float vy = randomRange(minSpeed, maxSpeed);

  if (rand() % 2) vx = -vx;
  if (rand() % 2) vy = -vy;

  velocity_ = {vx, vy};
}

void Ball::move(float deltaTime, int boundaryX, int boundaryY) {
  body_.move(velocity_ * deltaTime);

  sf::Vector2f pos = body_.getPosition();
  float diameter = body_.getRadius() * 2.0f;

  if (pos.x <= 0.0f || pos.x + diameter >= static_cast<float>(boundaryX)) {
    velocity_.x = -velocity_.x;
  }
  if (pos.y <= 0.0f || pos.y + diameter >= static_cast<float>(boundaryY)) {
    velocity_.y = -velocity_.y;
  }
}

void Ball::draw(sf::RenderWindow& target) { target.draw(body_); }

bool Ball::containsPoint(sf::Vector2i point) {
  return body_.getGlobalBounds().contains(static_cast<float>(point.x),
                                          static_cast<float>(point.y));
}

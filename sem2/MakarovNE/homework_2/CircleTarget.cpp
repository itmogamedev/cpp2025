#include "CircleTarget.h"

CircleTarget::CircleTarget(float x, float y, float radius,
                           const sf::Color& color, float windowWidth,
                           float windowHeight)
    : window_width_(windowWidth), window_height_(windowHeight) {
  shape_.setRadius(radius);
  shape_.setOrigin({radius, radius});
  shape_.setPosition({x, y});
  shape_.setFillColor(color);

  float speed = Utils::randomFloat(50.0f, 150.0f);
  float angel = Utils::randomFloat(0.0f, 360.0f);
  velocity_.x = speed * std::cos(angel * 3.1415f / 180.0f);
  velocity_.y = speed * std::sin(angel * 3.1415f / 180.0f);
}

void CircleTarget::draw(sf::RenderWindow& window) const { window.draw(shape_); }

void CircleTarget::move(sf::Time deltaTime) {
  sf::Vector2f currentPos = shape_.getPosition();
  float radius = shape_.getRadius();

  if (currentPos.x - radius < 0 || currentPos.x + radius > window_width_) {
    velocity_.x *= -1;

    if (currentPos.x - radius < 0)
      shape_.setPosition({radius + 1, currentPos.y});
    else
      shape_.setPosition({window_width_ - radius - 1, currentPos.y});
  }

  if (currentPos.y - radius < 0 || currentPos.y + radius > window_height_) {
    velocity_.y *= -1;

    if (currentPos.y - radius < 0)
      shape_.setPosition({currentPos.x, radius + 1});
    else
      shape_.setPosition({currentPos.x, window_height_ - radius - 1});
  }

  shape_.move(velocity_ * deltaTime.asSeconds());
}

sf::Vector2f CircleTarget::getPosition() const { return shape_.getPosition(); }
float CircleTarget::getRadius() const { return shape_.getRadius(); }

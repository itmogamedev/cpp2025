#include "Circle.h"

#include <cmath>
#include <cstdlib>

#include "Constants.h"

Circle::Circle(float radius, sf::Color color) : radius_(radius) {
  shape_.setRadius(radius_);
  shape_.setFillColor(color);
  shape_.setOutlineColor(sf::Color::White);
  shape_.setOutlineThickness(constants::kCircleOutlineThickness);
  shape_.setOrigin({radius_, radius_});
}

void Circle::randomize(float window_width, float window_height) {
  float range_x = window_width - 2.f * radius_;
  float range_y = window_height - 2.f * radius_;

  float x = radius_ + static_cast<float>(std::rand()) /
                          (static_cast<float>(RAND_MAX) / range_x);
  float y = radius_ + static_cast<float>(std::rand()) /
                          (static_cast<float>(RAND_MAX) / range_y);
  shape_.setPosition({x, y});

  float speed =
      constants::kMinCircleSpeed +
      static_cast<float>(std::rand()) /
          (static_cast<float>(RAND_MAX) / constants::kMaxCircleSpeedBonus);
  float angle = static_cast<float>(std::rand()) /
                (static_cast<float>(RAND_MAX) / (2.f * 3.14159265f));
  velocity_ = {std::cos(angle) * speed, std::sin(angle) * speed};
}

void Circle::update(float delta_time, float window_width, float window_height) {
  shape_.move(velocity_ * delta_time);

  sf::Vector2f pos = shape_.getPosition();

  if (pos.x - radius_ < 0.f) {
    velocity_.x = std::abs(velocity_.x);
    shape_.setPosition({radius_, pos.y});
  } else if (pos.x + radius_ > window_width) {
    velocity_.x = -std::abs(velocity_.x);
    shape_.setPosition({window_width - radius_, pos.y});
  }

  pos = shape_.getPosition();

  if (pos.y - radius_ < 0.f) {
    velocity_.y = std::abs(velocity_.y);
    shape_.setPosition({pos.x, radius_});
  } else if (pos.y + radius_ > window_height) {
    velocity_.y = -std::abs(velocity_.y);
    shape_.setPosition({pos.x, window_height - radius_});
  }
}

void Circle::draw(sf::RenderWindow& window) const { window.draw(shape_); }

bool Circle::isClicked(sf::Vector2f mouse_pos) const {
  sf::Vector2f pos = shape_.getPosition();
  float dx = mouse_pos.x - pos.x;
  float dy = mouse_pos.y - pos.y;
  return std::sqrt(dx * dx + dy * dy) <= radius_;
}

#include "target.h"

#include <cmath>
#include <cstdlib>

#include "game_config.h"

Target::Target(float radius, const std::vector<sf::Texture>& textures)
    : radius_(radius), textures_(&textures) {
  fallback_.setRadius(radius_);
  fallback_.setOrigin(radius_, radius_);
  fallback_.setFillColor(sf::Color(220, 70, 70, 210));
  fallback_.setOutlineColor(sf::Color::White);
  fallback_.setOutlineThickness(3.f);
}

void Target::applyTexture(std::size_t idx) {
  if (!textures_ || textures_->empty()) return;
  sprite_.setTexture((*textures_)[idx]);
  const sf::Vector2u sz = (*textures_)[idx].getSize();
  sprite_.setOrigin(sz.x / 2.f, sz.y / 2.f);
  sprite_.setScale((radius_ * 2.f) / static_cast<float>(sz.x),
                   (radius_ * 2.f) / static_cast<float>(sz.y));
}

void Target::bounceWalls(unsigned int field_w, unsigned int field_h) {
  const float right = static_cast<float>(field_w);
  const float bottom = static_cast<float>(field_h);

  if (position_.x - radius_ < 0.f) {
    position_.x = radius_;
    velocity_.x = std::abs(velocity_.x);
  }
  if (position_.x + radius_ > right) {
    position_.x = right - radius_;
    velocity_.x = -std::abs(velocity_.x);
  }
  if (position_.y - radius_ < 0.f) {
    position_.y = radius_;
    velocity_.y = std::abs(velocity_.y);
  }
  if (position_.y + radius_ > bottom) {
    position_.y = bottom - radius_;
    velocity_.y = -std::abs(velocity_.y);
  }
}

void Target::randomize(unsigned int field_w, unsigned int field_h) {
  if (textures_ && !textures_->empty()) {
    applyTexture(static_cast<std::size_t>(std::rand()) % textures_->size());
  }

  const int uw = static_cast<int>(field_w) - static_cast<int>(radius_ * 2.f);
  const int uh = static_cast<int>(field_h) - static_cast<int>(radius_ * 2.f);
  position_.x = radius_ + static_cast<float>(std::rand() % (uw > 1 ? uw : 1));
  position_.y = radius_ + static_cast<float>(std::rand() % (uh > 1 ? uh : 1));

  constexpr float kTwoPi = 6.28318530f;
  const float t =
      static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
  const float speed = GameConfig::kMinSpeed +
                      t * (GameConfig::kMaxSpeed - GameConfig::kMinSpeed);
  const float angle =
      (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * kTwoPi;
  velocity_ = {speed * std::cos(angle), speed * std::sin(angle)};

  sprite_.setPosition(position_);
  fallback_.setPosition(position_);
}

void Target::update(float dt, unsigned int field_w, unsigned int field_h) {
  position_ += velocity_ * dt;
  bounceWalls(field_w, field_h);
  sprite_.setPosition(position_);
  fallback_.setPosition(position_);
}

void Target::draw(sf::RenderWindow& window) const {
  if (textures_ && !textures_->empty())
    window.draw(sprite_);
  else
    window.draw(fallback_);
}

bool Target::isClicked(sf::Vector2f mouse_pos) const {
  const sf::Vector2f d = mouse_pos - position_;
  return (d.x * d.x + d.y * d.y) <= (radius_ * radius_);
}

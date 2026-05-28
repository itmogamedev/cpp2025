#include "player.h"

#include <algorithm>

#include "constants.h"

void Player::setup(const sf::Texture& texture) {
  shape.setSize({playerWidth, playerHeight});
  shape.setTexture(&texture);
  reset();
}

void Player::reset() {
  shape.setPosition(
      {(float(windowWidth) - playerWidth) / 2.0f, float(windowHeight) - 70.0f});
  shape.setFillColor(sf::Color::White);
  blink_left = 0.0f;
}

void Player::move(float direction, float time) {
  sf::Vector2f point = shape.getPosition();
  point.x += direction * playerSpeed * time;
  point.x = std::clamp(point.x, 0.0f, float(windowWidth) - playerWidth);
  shape.setPosition(point);
}

void Player::update(float time) {
  if (blink_left <= 0.0f) {
    shape.setFillColor(sf::Color::White);
    return;
  }

  blink_left = std::max(0.0f, blink_left - time);
  if (int(blink_left * 14.0f) % 2 == 0) {
    shape.setFillColor(sf::Color(255, 255, 255, 80));
  } else {
    shape.setFillColor(sf::Color::White);
  }
}

void Player::draw(sf::RenderWindow& window) const { window.draw(shape); }

sf::FloatRect Player::bounds() const { return shape.getGlobalBounds(); }

sf::Vector2f Player::shotPoint() const {
  sf::Vector2f point = shape.getPosition();
  return {point.x + playerWidth / 2.0f - shotWidth / 2.0f,
          point.y - shotHeight};
}

void Player::blink() { blink_left = 1.2f; }

bool Player::canBeHit() const { return blink_left <= 0.0f; }

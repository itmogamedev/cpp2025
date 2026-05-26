#include "player.h"

#include <algorithm>

#include "constants.h"

Player::Player() {
  shape.setPointCount(3);
  shape.setPoint(0, {constants::kPlayerRadius, 0.0F});
  shape.setPoint(1, {0.0F, constants::kPlayerRadius * 2.0F});
  shape.setPoint(
      2, {constants::kPlayerRadius * 2.0F, constants::kPlayerRadius * 2.0F});
  shape.setOrigin({constants::kPlayerRadius, constants::kPlayerRadius});
  shape.setFillColor(sf::Color(80, 190, 255));
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(2.0F);
  resetPosition();
}

void Player::update(float delta_time) {
  float direction = 0.0F;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    direction -= 1.0F;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    direction += 1.0F;
  }

  shape.move({direction * constants::kPlayerSpeed * delta_time, 0.0F});

  const float min_x = constants::kPlayerRadius;
  const float max_x =
      static_cast<float>(constants::kWindowWidth) - constants::kPlayerRadius;
  sf::Vector2f position = shape.getPosition();
  position.x = std::clamp(position.x, min_x, max_x);
  shape.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) const { window.draw(shape); }

void Player::resetPosition() {
  shape.setPosition({static_cast<float>(constants::kWindowWidth) / 2.0F,
                     static_cast<float>(constants::kWindowHeight) - 70.0F});
}

sf::Vector2f Player::getGunPosition() const {
  sf::Vector2f position = shape.getPosition();
  return {position.x, position.y - constants::kPlayerRadius};
}

sf::Vector2f Player::getPosition() const { return shape.getPosition(); }

sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }

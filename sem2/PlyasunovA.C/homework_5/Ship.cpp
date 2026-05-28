#include "Ship.h"

Ship::Ship() : speed(300.f) {
  shape.setSize(sf::Vector2f(kShipWidth, kShipHeight));
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(400.f - kShipWidth / 2, 550.f);
}

void Ship::update(sf::Time delta_time) {
  float dt = delta_time.asSeconds();
  sf::Vector2f pos = shape.getPosition();
  pos += velocity * dt;
  if (pos.x < kLeftBound) pos.x = kLeftBound;
  if (pos.x + kShipWidth > kRightBound) pos.x = kRightBound - kShipWidth;
  shape.setPosition(pos);
  velocity.x = 0.f;
}

void Ship::draw(sf::RenderWindow& window) { window.draw(shape); }

void Ship::handleInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x = -speed;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x = speed;
  }
}

sf::FloatRect Ship::getBounds() const { return shape.getGlobalBounds(); }

void Ship::resetPosition() { shape.setPosition(400.f - kShipWidth / 2, 550.f); }

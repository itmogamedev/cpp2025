#include "Player.h"

#include <SFML/Window/Keyboard.hpp>

Player::Player() {
  shape.setSize(sf::Vector2f(50.f, 50.f));
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(sf::Vector2f(375.f, 530.f));
  movementSpeed = 7.f;
}

void Player::update() {
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) &&
      shape.getPosition().x > 0) {
    shape.move(sf::Vector2f(-movementSpeed, 0.f));
  }
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
      shape.getPosition().x < 750) {
    shape.move(sf::Vector2f(movementSpeed, 0.f));
  }
}

void Player::render(sf::RenderTarget& target) const { target.draw(shape); }

sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }

sf::Vector2f Player::getPosition() const { return shape.getPosition(); }